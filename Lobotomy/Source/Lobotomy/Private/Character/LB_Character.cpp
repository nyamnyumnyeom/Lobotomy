#include "Character/LB_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/LB_PlayerController.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "InteractComponent.h"
#include "Components/AudioComponent.h"

ALB_Character::ALB_Character()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(GetCapsuleComponent());
    SpringArmComponent->TargetArmLength = 0.0f;
    SpringArmComponent->bUsePawnControlRotation = true;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(SpringArmComponent);
    FirstPersonCamera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    WalkSpeed = 300.0f;
    SprintSpeed = 450.0f;

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    FootstepDistanceThreshold = 170.0f;
    DistanceTraveled = 0.0f;

    NoiseLoudness = 0.7f;

    bIsWalking = false;
    bIsRunning = false;
    bWasWalking = false;
    bWasRunning = false;

    InteractionTraceDistance = 300.0f;
    InteractionSphereRadius = 30.0f;
    CurrentInteractActor = nullptr;
}

void ALB_Character::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ALB_Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const FVector Velocity = GetCharacterMovement()->Velocity;
    const float HorizontalSpeed = FVector(Velocity.X, Velocity.Y, 0).Size();
    const float DistanceThisFrame = HorizontalSpeed * DeltaTime;
    DistanceTraveled += DistanceThisFrame;

    while (DistanceTraveled >= FootstepDistanceThreshold)
    {
        DistanceTraveled -= FootstepDistanceThreshold;
        if (FootstepSounds.Num() > 0)
        {
            const int32 RandomIndex = FMath::RandRange(0, FootstepSounds.Num() - 1);
            USoundBase* SoundToPlay = FootstepSounds[RandomIndex];
            if (SoundToPlay)
            {
                UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());

                MakeNoise(NoiseLoudness, this, GetActorLocation());
            }
        }
    }
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

    if (HorizontalSpeed > 0.f && HorizontalSpeed <= WalkSpeed)
    {
        if (!bWasWalking)
        {
            StartWalking();
            bWasWalking = true;
            bWasRunning = false;
        }
    }
    else if (HorizontalSpeed > WalkSpeed)
    {
        if (!bWasRunning)
        {
            StartRunning();
            bWasWalking = false;
            bWasRunning = true;
        }
    }
    else
    {
        if (bWasWalking || bWasRunning)
        {
            StopMoving();
            bWasWalking = false;
            bWasRunning = false;
        }
    }

    FVector Start = FirstPersonCamera->GetComponentLocation();
    FVector End = Start + (FirstPersonCamera->GetForwardVector() * InteractionTraceDistance);
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        Start,
        End,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeSphere(InteractionSphereRadius),
        Params
    );

    AActor* HitActor = bHit ? HitResult.GetActor() : nullptr;

    if (HitActor != CurrentInteractActor)
    {

        if (CurrentInteractActor)
        {
            if (UInteractComponent* OldInteractComp = CurrentInteractActor->FindComponentByClass<UInteractComponent>())
            {
                OldInteractComp->HideWidget();
            }
        }

        if (HitActor)
        {
            if (UInteractComponent* NewInteractComp = HitActor->FindComponentByClass<UInteractComponent>())
            {
                NewInteractComp->ShowWidget();
            }
        }
        CurrentInteractActor = HitActor;
    }

    if (HeartbeatAudioComponent && HeartbeatTarget)
    {
        float Distance = FVector::Distance(GetActorLocation(), HeartbeatTarget->GetActorLocation());

        // 볼륨 계산 (기존)
        float Alpha = 1.f - FMath::Clamp((Distance - MinDistance) / (MaxDistance - MinDistance), 0.f, 1.f);
        float CurveAlpha = FMath::InterpEaseInOut(0.f, 1.f, Alpha, 2.f);
        float NewVolume = FMath::Lerp(MinVolume, MaxVolume, CurveAlpha);
        HeartbeatAudioComponent->SetVolumeMultiplier(NewVolume);

        // 박동 속도 계산
        float NewPitch = FMath::Lerp(MinPitch, MaxPitch, CurveAlpha);
        HeartbeatAudioComponent->SetPitchMultiplier(NewPitch);
    }
}

void ALB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ALB_PlayerController* PlayerController = Cast<ALB_PlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ALB_Character::Move);
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ALB_Character::Look);
            }

            if (PlayerController->SprintAction)
            {
                EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Started, this, &ALB_Character::StartSprint);
                EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &ALB_Character::StopSprint);
            }
            if (PlayerController->InteractAction)
            {
                EnhancedInput->BindAction(PlayerController->InteractAction, ETriggerEvent::Triggered, this, &ALB_Character::Interact);
            }
        }
    }
}

void ALB_Character::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller)
    {
        // 카메라 방향 기준으로 이동 (Pitch 무시, Yaw만 사용)
        FRotator ControlRotation = Controller->GetControlRotation();
        FRotator YawRotation(0, ControlRotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ALB_Character::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    AddControllerYawInput(LookAxisVector.X);   // 좌우 회전
    AddControllerPitchInput(LookAxisVector.Y); // 위아래 회전
}

void ALB_Character::Interact(const FInputActionValue& Value)
{
    if (CurrentInteractActor)
    {
        if (UInteractComponent* InterComp = CurrentInteractActor->FindComponentByClass<UInteractComponent>())
        {
            UE_LOG(LogTemp, Warning, TEXT("InteractComponent found on %s"), *CurrentInteractActor->GetName());
            InterComp->Interact(this);
        }

    }
}

void ALB_Character::StartSprint()
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
        NoiseLoudness = 1.5f;
    }
}

void ALB_Character::StopSprint()
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        NoiseLoudness = 0.8f;
    }
}


void ALB_Character::StartWalking()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (PC->PlayerCameraManager && WalkShakeClass)
        {
            PC->PlayerCameraManager->StartCameraShake(WalkShakeClass, 1.0f);
        }
    }
}

void ALB_Character::StartRunning()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (PC->PlayerCameraManager && RunShakeClass)
        {
            PC->PlayerCameraManager->StartCameraShake(RunShakeClass, 1.0f);
        }
    }
}


void ALB_Character::StopMoving()
{
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (PC->PlayerCameraManager)
        {
            PC->PlayerCameraManager->StopAllCameraShakes(true);
        }
    }
}

void ALB_Character::StartHeartbeat()
{
    if (HeartbeatSound && !HeartbeatAudioComponent)
    {
        HeartbeatAudioComponent = UGameplayStatics::SpawnSound2D(
            this,
            HeartbeatSound,
            MinVolume,
            1.f,
            0.f,
            nullptr,
            true
        );
    }
}

void ALB_Character::StopHeartbeat()
{
    if (HeartbeatAudioComponent.Get())
    {
        HeartbeatAudioComponent.Get()->Stop();
        HeartbeatAudioComponent = nullptr;
    }
}

void ALB_Character::SetHeartbeatTarget(AActor* NewTarget)
{
    HeartbeatTarget = NewTarget;
}