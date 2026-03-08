// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_KKeek.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Component/LB_KKeekComp.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LB_GM.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "LevelActor/LB_TargetPoint_KKE.h"
#include "NavigationPath.h"
#include "EngineUtils.h"

ALB_Monster_KKeek::ALB_Monster_KKeek()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("KKeek"));
}

void ALB_Monster_KKeek::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();

	ResistForPlayer();

	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;

	AAIController* AICon = Cast<AAIController>(GetController());
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (AICon && Player)
	{
		AICon->SetFocus(Player);
	}
}

void ALB_Monster_KKeek::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWalkingRight)
	{
		WalkElapsedTime += DeltaTime;

		AddMovementInput(GetActorRightVector(), 1.0f);

		if (WalkElapsedTime >= WalkDuration)
		{
			bIsWalkingRight = false;
		}
	}
}

void ALB_Monster_KKeek::KKeekKKeekInvisible()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoInvisibleTimerHandle);
	}

	AAIController* AICon = Cast<AAIController>(GetController());
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (AICon && Player)
	{
		AICon->SetFocus(nullptr);
	}

	bIsWalkingRight = false;

	MoveToFarthestReachableTarget();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(AutoInvisibleTimerHandle, this, &ALB_Monster_KKeek::KKERealInvisible, 10.0f, false);
	}
}

void ALB_Monster_KKeek::KKeekKKeekVisible(FVector NewLocation)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

	AAIController* AICon = Cast<AAIController>(GetController());
	if (AICon && Player)
	{
		AICon->SetFocus(Player);
	}

	KKeekComp_Ref->bIsKKeekHere = true;

	SetActorHiddenInGame(false);

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetVisibility(true, true);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
	}

	FVector PlayerLocation = Player->GetActorLocation();
	FVector PlayerRight = Player->GetActorRightVector();

	FVector AdjustedLocation = NewLocation + PlayerRight * RightOffset;
	
	FVector SpawnLocation = NewLocation;

	FRotator LookAtRot = (PlayerLocation - AdjustedLocation).Rotation();
	LookAtRot.Pitch = 0.0f;
	LookAtRot.Roll = 0.0f;

	SetActorLocationAndRotation(
		AdjustedLocation,
		LookAtRot,
		false,
		nullptr,
		ETeleportType::TeleportPhysics
	);

	if ((PlayerLocation - NewLocation).Length() < PlayerKillDistance)
	{
		ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));

		FVector KillMontageLocation = NewLocation;
		KillMontageLocation.Z += 60.0f;

		SetActorLocation(KillMontageLocation);

		PlayKillMontage(1.0f);

		GM->PlayerDeathLogic(GetActorLocation(), 2);

		return;
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}

	WalkElapsedTime = 0.0f;
	bIsWalkingRight = true;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(AutoInvisibleTimerHandle, this, &ALB_Monster_KKeek::KKeekKKeekWatchThePlayer, WalkDuration, false);
	}

	// SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
}

void ALB_Monster_KKeek::KKeekKKeekWatchThePlayer()
{
	bIsWalkingRight = false;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	AnimInstance->Montage_Play(WatchMontage, 1.0f);
}

void ALB_Monster_KKeek::PlayKillMontage(float PlayRate)
{
	if (!PlayMontage) return;

	GetCharacterMovement()->DisableMovement();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	AnimInstance->Montage_Play(PlayMontage, PlayRate);
}

void ALB_Monster_KKeek::ResistForPlayer()
{
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerChar)
	{
		KKeekComp_Ref = PlayerChar->FindComponentByClass<ULB_KKeekComp>();
		if (KKeekComp_Ref)
		{
			KKeekComp_Ref->ResistKKeek(this);
		}
		else
		{
			if (GetWorld())
			{
				GetWorld()->GetTimerManager().SetTimer(ResistTimerHandle, this, &ALB_Monster_KKeek::ResistForPlayer, 1.0f, false);
			}
		}
	}
}

void ALB_Monster_KKeek::MoveToFarthestReachableTarget()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if (!AICon) return;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys) return;

	FVector MyLocation = GetActorLocation();

	float MaxPathLength = 0.0f;
	ALB_TargetPoint_KKE* FarthestTarget = nullptr;

	for (TActorIterator<ALB_TargetPoint_KKE> It(GetWorld()); It; ++It)
	{
		ALB_TargetPoint_KKE* Target = *It;
		if (!Target) continue;

		UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(
			GetWorld(),
			MyLocation,
			Target->GetActorLocation(),
			this
		);

		if (NavPath && NavPath->IsValid() && NavPath->PathPoints.Num() > 1)
		{
			float PathLength = NavPath->GetPathLength();

			if (PathLength > MaxPathLength)
			{
				MaxPathLength = PathLength;
				FarthestTarget = Target;
			}
		}
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance->Montage_IsPlaying(WatchMontage))
	{
		AnimInstance->Montage_Stop(0.2f, WatchMontage);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = RunawaySpeed;
	}

	if (FarthestTarget)
	{
		AICon->MoveToActor(FarthestTarget);
	}
}

void ALB_Monster_KKeek::KKERealInvisible()
{
	KKeekComp_Ref->bIsKKeekHere = false;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance->Montage_IsPlaying(WatchMontage))
	{
		AnimInstance->Montage_Stop(0.2f, WatchMontage);
	}

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetVisibility(false, true);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	SetActorLocation(OriginLocation, false, nullptr, ETeleportType::TeleportPhysics);
}
