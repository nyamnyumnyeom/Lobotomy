#include "LB_BuzzWireActor.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ALB_BuzzWireActor::ALB_BuzzWireActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	FocusCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FocusCamera"));
	FocusCamera->SetupAttachment(Root);

	RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh"));
	RingMesh->SetupAttachment(Root);
	//RingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DeadZoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeadZoneMesh"));
	DeadZoneMesh->SetupAttachment(Root);
	//DeadZoneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SuccessZoneCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SuccessZoneCollision"));
	SuccessZoneCollision->SetupAttachment(Root);
	SuccessZoneCollision->SetBoxExtent(FVector(60, 60, 60));
	SuccessZoneCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SuccessZoneCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SuccessZoneCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SuccessZoneCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SuccessZoneCollision->OnComponentBeginOverlap.AddDynamic(
		this, &ALB_BuzzWireActor::HandleSuccessZoneBeginOverlap);

	SPZone1Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SPZone1Collision"));
	SPZone1Collision->SetupAttachment(Root);
	SPZone1Collision->SetBoxExtent(FVector(50, 50, 50));
	SPZone1Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SPZone1Collision->SetCollisionObjectType(ECC_WorldDynamic);
	SPZone1Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SPZone1Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SPZone1Collision->OnComponentBeginOverlap.AddDynamic(
		this, &ALB_BuzzWireActor::HandleSPZone1BeginOverlap);

	SPZone2Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SPZone2Collision"));
	SPZone2Collision->SetupAttachment(Root);
	SPZone2Collision->SetBoxExtent(FVector(50, 50, 50));
	SPZone2Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SPZone2Collision->SetCollisionObjectType(ECC_WorldDynamic);
	SPZone2Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SPZone2Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SPZone2Collision->OnComponentBeginOverlap.AddDynamic(
		this, &ALB_BuzzWireActor::HandleSPZone2BeginOverlap);

	SPZone3Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SPZone3Collision"));
	SPZone3Collision->SetupAttachment(Root);
	SPZone3Collision->SetBoxExtent(FVector(50, 50, 50));
	SPZone3Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SPZone3Collision->SetCollisionObjectType(ECC_WorldDynamic);
	SPZone3Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SPZone3Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SPZone3Collision->OnComponentBeginOverlap.AddDynamic(
		this, &ALB_BuzzWireActor::HandleSPZone3BeginOverlap);

	InBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InBox"));
	InBox->SetupAttachment(RingMesh);
	InBox->SetBoxExtent(FVector(7, 20, 7));
	InBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	InBox->OnComponentBeginOverlap.AddDynamic(this, &ALB_BuzzWireActor::HandleInBegin);
	InBox->OnComponentEndOverlap.AddDynamic(this, &ALB_BuzzWireActor::HandleInEnd);

	OutBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OutBox"));
	OutBox->SetupAttachment(RingMesh);
	OutBox->SetBoxExtent(FVector(18, 20, 18));
	OutBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	OutBox->OnComponentBeginOverlap.AddDynamic(this, &ALB_BuzzWireActor::HandleOutBegin);
	OutBox->OnComponentEndOverlap.AddDynamic(this, &ALB_BuzzWireActor::HandleOutEnd);
}

void ALB_BuzzWireActor::BeginPlay()
{
	Super::BeginPlay();
}

void ALB_BuzzWireActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bBuzzActive && !bDeadTriggered && !bSuccessTriggered)
	{
		UpdateRingFollowMouse(DeltaSeconds);
	}
}

void ALB_BuzzWireActor::BuzzPlay(float BlendTime)
{
	CachedPC = UGameplayStatics::GetPlayerController(this, 0);
	if (!CachedPC) return;

	PreviousViewTarget = CachedPC->GetViewTarget();

	EnableInput(CachedPC);
	if (InputComponent)
	{
		InputComponent->ClearActionBindings();

		InputComponent->BindKey(EKeys::MouseScrollUp, IE_Pressed, this, &ALB_BuzzWireActor::RotateRingUp);
		InputComponent->BindKey(EKeys::MouseScrollDown, IE_Pressed, this, &ALB_BuzzWireActor::RotateRingDown);
	}

	CachedPC->SetViewTargetWithBlend(this, BlendTime);
	ApplyMouseOnlyInputLock(CachedPC);

	bDeadTriggered = false;
	bSuccessTriggered = false;
	bBuzzActive = true;
}

void ALB_BuzzWireActor::BuzzStop(float BlendTime)
{
	if (!CachedPC)
	{
		CachedPC = UGameplayStatics::GetPlayerController(this, 0);
	}

	if (CachedPC)
	{
		RestoreInput(CachedPC);
		if (PreviousViewTarget)
		{
			CachedPC->SetViewTargetWithBlend(PreviousViewTarget, BlendTime);
		}
		DisableInput(CachedPC);
	}

	EndBuzzSession();
}

void ALB_BuzzWireActor::EndBuzzSession()
{
	bBuzzActive = false;
	bDeadTriggered = false;
	bSuccessTriggered = false;
	bSpzone1ov = false;
	bSpzone2ov = false;
	bSpzone3ov = false;
}

void ALB_BuzzWireActor::SetBuzzActive(bool bNewActive)
{
	bBuzzActive = bNewActive;
}

void ALB_BuzzWireActor::ApplyMouseOnlyInputLock(APlayerController* PC)
{
	if (!PC) return;

	PC->SetIgnoreMoveInput(true);
	PC->SetIgnoreLookInput(true);

	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;

	FInputModeGameAndUI Mode;
	Mode.SetHideCursorDuringCapture(false);
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PC->SetInputMode(Mode);
}

void ALB_BuzzWireActor::RestoreInput(APlayerController* PC)
{
	if (!PC) return;

	PC->SetIgnoreMoveInput(false);
	PC->SetIgnoreLookInput(false);

	PC->bShowMouseCursor = false;
	PC->bEnableClickEvents = false;
	PC->bEnableMouseOverEvents = false;

	FInputModeGameOnly Mode;
	PC->SetInputMode(Mode);
}

void ALB_BuzzWireActor::UpdateRingFollowMouse(float DeltaSeconds) {
		if (!CachedPC) return;
		FVector WorldLocation, WorldDirection;
		if (CachedPC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
				FVector PlaneOrigin = GetActorLocation();
				FVector PlaneNormal = FVector(1.0f, 0.0f, 0.0f);
				FVector RayStart = WorldLocation;
				FVector RayEnd = WorldLocation + (WorldDirection * 10000.f);
				FVector TargetLocation = FMath::LinePlaneIntersection(RayStart, RayEnd, PlaneOrigin, PlaneNormal);
				TargetLocation += RingWorldOffset;
				FVector CurrentLoc = RingMesh->GetComponentLocation();
				FVector NewLoc = FMath::VInterpTo(CurrentLoc, TargetLocation, DeltaSeconds, FollowInterpSpeed);
				RingMesh->SetWorldLocation(NewLoc);
		}
}

//void ALB_BuzzWireActor::CheckDistanceToRod()
//{
//	if (!TargetSpline) return;
//
//	const FVector RingLocation = RingMesh->GetComponentLocation();
//
//	const FVector Closest =
//		TargetSpline->FindLocationClosestToWorldLocation(
//			RingLocation, ESplineCoordinateSpace::World);
//
//	const float Distance = FVector::Dist(RingLocation, Closest);
//
//	if (Distance <= DangerRadius)
//	{
//		bDeadTriggered = true;
//		bBuzzActive = false;
//		OnBuzzDeath();
//	}
//}

void ALB_BuzzWireActor::HandleSuccessZoneBeginOverlap(
	UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;
	if (!bSpzone1ov || !bSpzone2ov || !bSpzone3ov) return;

	bSuccessTriggered = true;
	bBuzzActive = false;
	OnBuzzSuccess();
}

void ALB_BuzzWireActor::HandleSPZone1BeginOverlap(
	UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;
	OnSPZone1();
}

void ALB_BuzzWireActor::HandleSPZone2BeginOverlap(
	UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;
	OnSPZone2();
}

void ALB_BuzzWireActor::HandleSPZone3BeginOverlap(
	UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;
	OnSPZone3();
}

void ALB_BuzzWireActor::RotateRingUp()
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

	RingMesh->AddLocalRotation(FRotator( 0.f, RingRotationStep, 0.f));
}

void ALB_BuzzWireActor::RotateRingDown()
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

	RingMesh->AddLocalRotation(FRotator( 0.f, -RingRotationStep, 0.f));
}

void ALB_BuzzWireActor::HandleInBegin(
	UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32, bool, const FHitResult&)
{
	if (OtherComp == DeadZoneMesh)
	{
		bInOverlap = true;
		EvaluateDead();
	}

}

void ALB_BuzzWireActor::HandleInEnd(
	UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32)
{
	if (OtherComp == DeadZoneMesh)
	{
		bInOverlap = false;
		EvaluateDead();
	}
}

void ALB_BuzzWireActor::HandleOutBegin(
	UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32, bool, const FHitResult&)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap With: %s"), *GetNameSafe(OtherComp));
	if (OtherComp == DeadZoneMesh)
	{
		bOutOverlap = true;
		EvaluateDead();
	}

}

void ALB_BuzzWireActor::HandleOutEnd(
	UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32)
{
	if (OtherComp == DeadZoneMesh)
	{
		bOutOverlap = false;
		EvaluateDead();
	}
}

void ALB_BuzzWireActor::EvaluateDead()
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

	if (bOutOverlap && !bInOverlap)
	{
		bDeadTriggered = true;
		bBuzzActive = false;
		bSpzone1ov = false;
		bSpzone2ov = false;
		bSpzone3ov = false;
		OnBuzzDeath();
	}
}