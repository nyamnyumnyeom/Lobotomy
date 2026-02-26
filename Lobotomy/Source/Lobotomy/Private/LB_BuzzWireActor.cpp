#include "LB_BuzzWireActor.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
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
		CheckDistanceToRod();
	}
}

void ALB_BuzzWireActor::BuzzPlay(float BlendTime)
{
	CachedPC = UGameplayStatics::GetPlayerController(this, 0);
	if (!CachedPC) return;

	PreviousViewTarget = CachedPC->GetViewTarget();

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
	}

	EndBuzzSession();
}

void ALB_BuzzWireActor::EndBuzzSession()
{
	bBuzzActive = false;
	bDeadTriggered = false;
	bSuccessTriggered = false;
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

void ALB_BuzzWireActor::UpdateRingFollowMouse(float DeltaSeconds)
{
	if (!CachedPC) return;

	FHitResult Hit;
	const bool bHit = CachedPC->GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(MouseTraceChannel),
		true,
		Hit
	);

	if (!bHit) return;

	FVector Target = Hit.ImpactPoint + RingWorldOffset;
	const FVector Current = RingMesh->GetComponentLocation();
	Target.X = Current.X;
	// Target.X = GetActorLocation().X; 

	const FVector NewLoc = FMath::VInterpTo(Current, Target, DeltaSeconds, FollowInterpSpeed);

	RingMesh->SetWorldLocation(NewLoc);
}

void ALB_BuzzWireActor::CheckDistanceToRod()
{
	if (!TargetSpline) return;

	const FVector RingLocation = RingMesh->GetComponentLocation();

	const FVector Closest =
		TargetSpline->FindLocationClosestToWorldLocation(
			RingLocation, ESplineCoordinateSpace::World);

	const float Distance = FVector::Dist(RingLocation, Closest);

	if (Distance <= DangerRadius)
	{
		bDeadTriggered = true;
		bBuzzActive = false;
		OnBuzzDeath();
	}
}

void ALB_BuzzWireActor::HandleSuccessZoneBeginOverlap(
	UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

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