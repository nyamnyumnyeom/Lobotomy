// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_KKeek.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Component/LB_KKeekComp.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALB_Monster_KKeek::ALB_Monster_KKeek()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("KKeek"));
}

void ALB_Monster_KKeek::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();

	ResistForPlayer();
}

void ALB_Monster_KKeek::KKeekKKeekInvisible()
{
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

	SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
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
