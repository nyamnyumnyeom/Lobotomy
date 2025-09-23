// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_ChainSawMan.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"

ALB_Monster_ChainSawMan::ALB_Monster_ChainSawMan()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void ALB_Monster_ChainSawMan::BeginPlay()
{
	Super::BeginPlay();

	SpawnLogic();
}

bool ALB_Monster_ChainSawMan::CheakShouldDestroy_Implementation()
{
	if (!bIsSpawnDurationOver) return false;

	APawn* TargetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerForward = TargetActor->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (GetActorLocation() - TargetActor->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	if (Dot <= 0)
	{
		DisappearLogic();

		return true;
	}

	return false;
}

void ALB_Monster_ChainSawMan::SpawnLogic()
{
	SetSpawnWhetherToGM(true);

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnDurationTimerHandle);
		GetWorldTimerManager().SetTimer(SpawnDurationTimerHandle, this, &ALB_Monster_ChainSawMan::TimeupSpawnDuration, SpawnDuration, false);
	}
}

void ALB_Monster_ChainSawMan::DisappearLogic()
{
	SetSpawnWhetherToGM(false);

	Destroy();
}

void ALB_Monster_ChainSawMan::SetSpawnWhetherToGM(bool Value)
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->SetIsChainSawManSpawned(Value);
	}
}

void ALB_Monster_ChainSawMan::TimeupSpawnDuration()
{
	bIsSpawnDurationOver = true;
}
