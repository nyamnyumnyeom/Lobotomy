#include "LB_BuzzWireActor.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
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

	// =========================
	// Ring (Visual)
	// =========================
	RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh"));
	RingMesh->SetupAttachment(Root);
	RingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 링 메시 자체는 충돌 안씀 (판정은 Sphere로)

	// =========================
	// Ring Collision (판정용)
	// =========================
	RingCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RingCollision"));
	RingCollision->SetupAttachment(RingMesh);
	RingCollision->SetSphereRadius(18.f);

	RingCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RingCollision->SetCollisionObjectType(ECC_WorldDynamic);
	RingCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	RingCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	// =========================
	// Dead Zone (복잡한 메시 그대로 판정)
	// =========================
	DeadZoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeadZoneMesh"));
	DeadZoneMesh->SetupAttachment(Root);

	// ✅ 복잡한 메시 모양 그대로 Overlap 판정
	DeadZoneMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DeadZoneMesh->SetCollisionObjectType(ECC_WorldDynamic);
	DeadZoneMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	DeadZoneMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	// ✅ 링이 닿으면 이벤트 발생
	DeadZoneMesh->OnComponentBeginOverlap.AddDynamic(
		this,
		&ALB_BuzzWireActor::HandleDeadZoneMeshBeginOverlap
	);

	// =========================
	// Success Zone (Box Collision)
	// =========================
	SuccessZoneCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SuccessZoneCollision"));
	SuccessZoneCollision->SetupAttachment(Root);
	SuccessZoneCollision->SetBoxExtent(FVector(60, 60, 60));
	SuccessZoneCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SuccessZoneCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SuccessZoneCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SuccessZoneCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SuccessZoneCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&ALB_BuzzWireActor::HandleSuccessZoneBeginOverlap
	);

	// =========================
	// SP Zones
	// =========================
	SPZone1Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SPZone1Collision"));
	SPZone1Collision->SetupAttachment(Root);
	SPZone1Collision->SetBoxExtent(FVector(50, 50, 50));
	SPZone1Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SPZone1Collision->SetCollisionObjectType(ECC_WorldDynamic);
	SPZone1Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SPZone1Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SPZone1Collision->OnComponentBeginOverlap.AddDynamic(
		this,
		&ALB_BuzzWireActor::HandleSPZone1BeginOverlap
	);

	SPZone2Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SPZone2Collision"));
	SPZone2Collision->SetupAttachment(Root);
	SPZone2Collision->SetBoxExtent(FVector(50, 50, 50));
	SPZone2Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SPZone2Collision->SetCollisionObjectType(ECC_WorldDynamic);
	SPZone2Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SPZone2Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SPZone2Collision->OnComponentBeginOverlap.AddDynamic(
		this,
		&ALB_BuzzWireActor::HandleSPZone2BeginOverlap
	);

	SPZone3Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("SPZone3Collision"));
	SPZone3Collision->SetupAttachment(Root);
	SPZone3Collision->SetBoxExtent(FVector(50, 50, 50));
	SPZone3Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SPZone3Collision->SetCollisionObjectType(ECC_WorldDynamic);
	SPZone3Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SPZone3Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SPZone3Collision->OnComponentBeginOverlap.AddDynamic(
		this,
		&ALB_BuzzWireActor::HandleSPZone3BeginOverlap
	);
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

	const FVector Target = Hit.ImpactPoint + RingWorldOffset;
	const FVector Current = RingMesh->GetComponentLocation();
	const FVector NewLoc = FMath::VInterpTo(Current, Target, DeltaSeconds, FollowInterpSpeed);

	RingMesh->SetWorldLocation(NewLoc);
}

bool ALB_BuzzWireActor::IsRingOverlap(UPrimitiveComponent* OtherComp) const
{
	return (OtherComp && OtherComp == RingCollision);
}

void ALB_BuzzWireActor::HandleDeadZoneMeshBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!bBuzzActive) return;
	if (bDeadTriggered || bSuccessTriggered) return;

	if (OtherComp == RingCollision)
	{
		bDeadTriggered = true;
		bBuzzActive = false;
		OnBuzzDeath();
	}
}

void ALB_BuzzWireActor::HandleSuccessZoneBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!bBuzzActive) return;
	if (bDeadTriggered || bSuccessTriggered) return;

	if (IsRingOverlap(OtherComp))
	{
		bSuccessTriggered = true;
		bBuzzActive = false;
		OnBuzzSuccess();
	}
}

void ALB_BuzzWireActor::HandleSPZone1BeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

	if (IsRingOverlap(OtherComp))
	{
		OnSPZone1();
	}
}

void ALB_BuzzWireActor::HandleSPZone2BeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

	if (IsRingOverlap(OtherComp))
	{
		OnSPZone2();
	}
}

void ALB_BuzzWireActor::HandleSPZone3BeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!bBuzzActive || bDeadTriggered || bSuccessTriggered) return;

	if (IsRingOverlap(OtherComp))
	{
		OnSPZone3();
	}
}