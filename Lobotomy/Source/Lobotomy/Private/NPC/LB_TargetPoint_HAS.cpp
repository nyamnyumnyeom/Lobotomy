// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_TargetPoint_HAS.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "NPC/LB_MonsterHideAndSeeker.h"
#include "NPC/LB_Monster_ChainSawMan.h"
#include "LB_GM.h"
#include "Kismet/GameplayStatics.h"

ALB_TargetPoint_HAS::ALB_TargetPoint_HAS()
{
	PrimaryActorTick.bCanEverTick = false;

	InsideBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	InsideBillboard->SetupAttachment(RootComponent);
	InsideBillboard->SetRelativeLocation(FVector(200.0f, 0.0f, 0.0f));
	InsideBillboard->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	InsideSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("InsideSpawnPoint"));
	InsideSpawnPoint->SetupAttachment(InsideBillboard);

	Tags.Add(FName("HideAndSeekPoint"));
}

void ALB_TargetPoint_HAS::BeginPlay()
{
	Super::BeginPlay();

}

void ALB_TargetPoint_HAS::HASSystemActivate(bool bIsOutDoor)
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		if (GM->GetShouldChainSawManSpawn())
		{
			if (GM->GetIsChainSawManSpawned())
			{
				if (GM->GetChainSawManToPlayerDistance() > RespawnDistance)
				{
					FVector SpawnLocation = GetActorLocation();
					FRotator SpawnRotation = GetActorRotation();
					if (!bIsOutDoor)
					{
						SpawnLocation = InsideBillboard->GetComponentLocation();
						SpawnRotation = InsideBillboard->GetComponentRotation();
					}

					FTransform SpawnTrans = FTransform(SpawnRotation, SpawnLocation, FVector(1.0f, 1.0f, 1.0f));
					GM->SetChainSawManTransform(SpawnTrans);
				}
			}
			else
			{
				SpawnLogic(ChainSawManClass, bIsOutDoor);
			}	

			GM->ResetKnockCount();
		}
		else
		{
			SpawnLogic(HideAndSeekerClass, bIsOutDoor);

			GM->AddKnockCount();
		}
	}
}

void ALB_TargetPoint_HAS::SpawnLogic(TSubclassOf<AActor> SpawnClass, bool bIsOutDoor)
{
	if (!SpawnClass) return;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	if (!bIsOutDoor)
	{
		SpawnLocation = InsideBillboard->GetComponentLocation();
		SpawnRotation = InsideBillboard->GetComponentRotation();
	}

	FVector Start = SpawnLocation;
	FVector End = Start - FVector(0, 0, 300.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		SpawnLocation = HitResult.ImpactPoint;
	}

	if (SpawnClass)
	{
		if (SpawnClass == HideAndSeekerClass)
		{
			SpawnedHideAndSeeker = GetWorld()->SpawnActor<ALB_MonsterHideAndSeeker>(SpawnClass, SpawnLocation, SpawnRotation);
			if (SpawnedHideAndSeeker)
			{
				SpawnedHideAndSeeker->SetOwner(this);

			}
		}
		
		if (SpawnClass == ChainSawManClass)
		{
			SpawnedChainSawMan = GetWorld()->SpawnActor<ALB_Monster_ChainSawMan>(SpawnClass, SpawnLocation, SpawnRotation);
			if (SpawnedChainSawMan)
			{
				SpawnedChainSawMan->SetOwner(this);

			}
		}
	}
}
