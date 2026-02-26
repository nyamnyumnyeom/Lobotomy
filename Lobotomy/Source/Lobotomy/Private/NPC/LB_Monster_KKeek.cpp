// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_KKeek.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Component/LB_KKeekComp.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LB_GM.h"

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
}

void ALB_Monster_KKeek::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWalkingForward)
	{
		WalkElapsedTime += DeltaTime;

		AddMovementInput(GetActorForwardVector(), 1.0f);

		if (WalkElapsedTime >= WalkDuration)
		{
			bIsWalkingForward = false;
		}
	}
}

void ALB_Monster_KKeek::KKeekKKeekInvisible()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoInvisibleTimerHandle);
	}

	bIsWalkingForward = false;

	KKeekComp_Ref->bIsKKeekHere = false;

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

void ALB_Monster_KKeek::KKeekKKeekVisible(FVector NewLocation)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

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

	FRotator LookAtRot = (PlayerLocation - NewLocation).Rotation();
	LookAtRot.Pitch = 0.0f;
	LookAtRot.Roll = 0.0f;

	SetActorLocationAndRotation(
		NewLocation,
		LookAtRot,
		false,
		nullptr,
		ETeleportType::TeleportPhysics
	);

	if ((PlayerLocation - NewLocation).Length() < PlayerKillDistance)
	{
		ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));

		PlayKillMontage(1.0f);

		GM->PlayerDeathLogic(GetActorLocation(), 2);

		return;
	}

	WalkElapsedTime = 0.0f;
	bIsWalkingForward = true;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(AutoInvisibleTimerHandle, this, &ALB_Monster_KKeek::KKeekKKeekInvisible, 1.0f, false);
	}

	// SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
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
