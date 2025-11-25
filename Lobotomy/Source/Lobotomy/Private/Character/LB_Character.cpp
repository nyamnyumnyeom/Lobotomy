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
#include "DrawDebugHelpers.h"
#include "LB_Setting.h"
#include "UI/LB_InGameHud.h"
#include "LB_LockDoor.h"

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

    CurrentInteractActor = nullptr;

    BatteryLevel = 1.0f;

    bIsHUDVisible = false;

    CurrentItem = NAME_None;

    Stamina = 1.0f;
    MaxStamina = 1.0f;
    StaminaDrainRate = 0.15f;
    StaminaRecoverRate = 0.2f;
    MinSprintStamina = 0.5f;
    bWantsToSprint = false;
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

    // Debug// 디버그 라인 & 스피어 표시
    //DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, 0, 1.0f);

    //if (bHit)
    //{
    //    // 무언가에 부딪혔다면, 부딪힌 지점에 초록색 구체
    //    DrawDebugSphere(GetWorld(), HitResult.Location, 20.0f, 12, FColor::Green, false, -1.0f);
    //}
    //else
    //{
    //    // 아무것도 안 부딪혔으면 끝지점에 빨간 구체
    //    DrawDebugSphere(GetWorld(), End, 20.0f, 12, FColor::Red, false, -1.0f);
    //}
// Debug
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

    if (bWantsToSprint && Stamina > 0.0f)
    {
        // 소모
        Stamina -= StaminaDrainRate * DeltaTime;
        Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);

        if (Stamina <= 0.0f)
        {
            // 스태미너 바닥 -> 강제로 걷기
            StopSprint();
        }
    }
    else
    {
        // 회복 (달리는 중 아니거나 바닥임)
        if (Stamina < MaxStamina)
        {
            Stamina += StaminaRecoverRate * DeltaTime;
            Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
        }
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
                EnhancedInput->BindAction(PlayerController->InteractAction, ETriggerEvent::Started, this, &ALB_Character::Interact);
            }
            if (PlayerController->EscapeAction)
            {
                EnhancedInput->BindAction(PlayerController->EscapeAction, ETriggerEvent::Started, this, &ALB_Character::HandleEscape);
            }
            if (PlayerController->FlashlightAction)
            {
                EnhancedInput->BindAction(PlayerController->FlashlightAction, ETriggerEvent::Started, this, &ALB_Character::ToggleFlashlight_BP);
            }
            if (PlayerController->UseItemAction)
            {
                EnhancedInput->BindAction(PlayerController->UseItemAction, ETriggerEvent::Started, this, &ALB_Character::HandleUseItem);
            }
            if (PlayerController->ChartAction)
            {
                EnhancedInput->BindAction(PlayerController->ChartAction, ETriggerEvent::Started, this, &ALB_Character::HandleChart);
            }
            if (PlayerController->Dropaction)
            {
                EnhancedInput->BindAction(PlayerController->Dropaction, ETriggerEvent::Started, this, &ALB_Character::Dropaction);
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
    FVector2D Delta = Value.Get<FVector2D>();

    if (ULB_Setting* s = ULB_Setting::Get())
    {
        Sensitive = s->MouseSensitivite;
    }
    AddControllerYawInput(Delta.X*Sensitive);
    AddControllerPitchInput(Delta.Y* Sensitive);
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
    if (Stamina <= MinSprintStamina)
    {
        return;
    }

    bWantsToSprint = true;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
        NoiseLoudness = 1.5f;
    }
}


void ALB_Character::StopSprint()
{
    bWantsToSprint = false;

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

void ALB_Character::ResetHeartbeatTarget()
{
	HeartbeatTarget = nullptr;
}

void ALB_Character::ShowHUDUI()
{
    if (HUDUIInstance)
    {
        HUDUIInstance->SetVisibility(ESlateVisibility::Visible);
        bIsHUDVisible = true;
    }
}

void ALB_Character::HideHUDUI()
{
    if (HUDUIInstance)
    {
        HUDUIInstance->SetVisibility(ESlateVisibility::Hidden);
        bIsHUDVisible = false;

    }
}

void ALB_Character::PickupItem(FName ItemName)
{

    if (!CurrentItem.IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("이미 아이템이 있어서 줍기 실패! (ShowNoPickup 호출)"));

        ShowNoPickup();
        return;
    }

    CurrentItem = ItemName;


    if (ItemData)
    {
        static const FString Context(TEXT("GetItemRowFromCharacter"));
        FItemRow* Row = ItemData->FindRow<FItemRow>(ItemName, Context);
        if (Row)
        {
            if (HUDUIInstance)
            {
                ULB_InGameHud* HUD = Cast<ULB_InGameHud>(HUDUIInstance);
                if (HUD)
                {
                    HUD->UpdateInventory();
                }
            }
        }
    }
}

void ALB_Character::AddBattery(float Amount)
{
    BatteryLevel = FMath::Clamp(BatteryLevel + Amount, 0.0f, 1.0f);
    UE_LOG(LogTemp, Warning, TEXT("Battery Level: %f"), BatteryLevel);
}

void ALB_Character::UseItem()
{
    if (CurrentItem == NAME_None)
    {
        return;
    }
    if (!ItemData)
    {
        return;
    }

    static const FString Context(TEXT("UseItem"));
    FItemRow* ItemRow = ItemData->FindRow<FItemRow>(CurrentItem, Context);

    if (!ItemRow)
    {
        return;
    }

    bool bConsumed = false;

    switch (ItemRow->ItemType)
    {
    case EItemType::Battery:
        {

        AddBattery(0.2f);
        UE_LOG(LogTemp, Warning, TEXT("배터리 사용: 충전 완료"));

        bConsumed = true;
        break;
        }

    default:
        {
        UE_LOG(LogTemp, Warning, TEXT("이 아이템은 바로 사용할 수 없습니다. (Interaction 필요 등)"));
        bConsumed = false;
        Noitemuse();
        break;
        }
    }

    if (bConsumed)
    {
        CurrentItem = NAME_None;

        if (HUDUIInstance)
        {
            if (ULB_InGameHud* HUD = Cast<ULB_InGameHud>(HUDUIInstance))
            {
                HUD->UpdateInventory();
            }
        }
        OnInventoryUpdated(CurrentItem);
    }
}


void ALB_Character::HandleUseItem(const FInputActionValue& Value)
{
    UseItem();
}

void ALB_Character::ClearCurrentItem()
{
    if (CurrentItem != NAME_None)
    {
        UE_LOG(LogTemp, Warning, TEXT("Item cleared: %s"), *CurrentItem.ToString());
        CurrentItem = NAME_None;

        if (HUDUIInstance)
        {
            if (ULB_InGameHud* HUD = Cast<ULB_InGameHud>(HUDUIInstance))
            {
                HUD->UpdateInventory();
            }
        }
        OnInventoryUpdated(CurrentItem);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No item to clear."));
    }
}

const FItemRow* ALB_Character::GetCurrentItemData() const
{
    if (!ItemData || CurrentItem.IsNone())
        return nullptr;

    static const FString Context(TEXT("GetCurrentItemData"));
    return ItemData->FindRow<FItemRow>(CurrentItem, Context);
}

UClass* ALB_Character::GetCurrentItemClass() const
{
    if (!ItemData || CurrentItem.IsNone())
        return nullptr;

    static const FString Context(TEXT("GetCurrentItemClass"));
    if (const FItemRow* Row = ItemData->FindRow<FItemRow>(CurrentItem, Context))
    {
        UClass* LoadedClass = Row->ItemClass.LoadSynchronous();
        if (LoadedClass && LoadedClass->IsChildOf(AActor::StaticClass()))
        {
            return LoadedClass;
        }
    }

    return nullptr;
}

AActor* ALB_Character::SpawnCurrentItem()
{
    const FItemRow* CurrentRow = GetCurrentItemData();
    UClass* ItemClassToSpawn = GetCurrentItemClass();

    if (!ItemClassToSpawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("SpawnCurrentItem: Item Class is invalid or None."));
        return nullptr;
    }

    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FVector SpawnLocation = GetActorLocation();
    SpawnLocation.Z += 20.0f;
    FRotator SpawnRotation = GetActorRotation();

    AActor* SpawnedActor = World->SpawnActor<AActor>(ItemClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

    if (SpawnedActor)
    {
        if (CurrentRow && CurrentRow->ItemCode == FName("Battery"))
        {
            SpawnedActor->SetActorScale3D(FVector(5.f));
        }
        else if (CurrentRow && CurrentRow->ItemCode == FName("Key_Storage01"))
        {
            SpawnedActor->SetActorScale3D(FVector(2.f));
        }
        else if (CurrentRow && CurrentRow->ItemCode == FName("Key_Medi01"))
        {
            SpawnedActor->SetActorScale3D(FVector(2.f));
        }
        UPrimitiveComponent* MeshComp = nullptr;

        if (UStaticMeshComponent* StaticMesh = SpawnedActor->FindComponentByClass<UStaticMeshComponent>())
        {
            MeshComp = StaticMesh;
        }
        else if (USkeletalMeshComponent* SkeletalMesh = SpawnedActor->FindComponentByClass<USkeletalMeshComponent>())
        {
            MeshComp = SkeletalMesh;
        }

        if (MeshComp)
        {
            MeshComp->SetMobility(EComponentMobility::Movable);
            MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            MeshComp->SetSimulatePhysics(true);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SpawnedActor has no mesh component! %s"), *SpawnedActor->GetName());
        }
    }

    return SpawnedActor;
}