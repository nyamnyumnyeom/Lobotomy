// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_TargetPoint_HAS.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "NPC/LB_MonsterHideAndSeeker.h"
#include "NPC/LB_Monster_ChainSawMan.h"
#include "LB_GM.h"
#include "Kismet/GameplayStatics.h"
#include "LB_LockDoor.h"
#include "Character/LB_Character.h"
#include "AchievementSubsystem.h"

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

void ALB_TargetPoint_HAS::HASSystemActivate(bool bIsPlayerInRoom)
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		/*if (GM->GetShouldChainSawManSpawn())
		{
			if (GM->GetIsChainSawManSpawned())
			{
				if (GM->GetChainSawManToPlayerDistance() > RespawnDistance)
				{
					FVector SpawnLocation = GetActorLocation();
					FRotator SpawnRotation = GetActorRotation();
					if (bIsPlayerInRoom)
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
				SpawnLogic(ChainSawManClass, bIsPlayerInRoom);
			}	

			GM->ResetKnockCount();
		}*/
		//else
		//{
			SpawnLogic(HideAndSeekerClass, bIsPlayerInRoom);
		//}
	}
}

void ALB_TargetPoint_HAS::SpawnLogic(TSubclassOf<AActor> SpawnClass, bool bIsPlayerInRoom)
{
	if (!SpawnClass) return;

	if (bIsAttack) return;

	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;

	if (GM->GetShouldHASAttackMode())
	{
		if (CheckNearbyDoorOpened())
		{
			UWorld* World = GetWorld();
			if (!World) return;

			ACharacter* Player = UGameplayStatics::GetPlayerCharacter(World, 0);
			if (!Player) return;

			FVector PlayerLocation = Player->GetActorLocation();

			FVector Forward = Player->GetActorForwardVector();

			FVector SpawnLocation = PlayerLocation - (Forward * AnglyKnockerDistanceOffset);

			SpawnLocation.Z += AnglyKnockerZOffset;

			FRotator SpawnRotation = (PlayerLocation - SpawnLocation).Rotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (SpawnClass == HideAndSeekerClass)
			{
				SpawnedHideAndSeeker = GetWorld()->SpawnActor<ALB_MonsterHideAndSeeker>(SpawnClass, SpawnLocation, SpawnRotation, SpawnParams);
				if (SpawnedHideAndSeeker)
				{
					SpawnedHideAndSeeker->SetOwner(this);
					SpawnedHideAndSeeker->bIsAngry = true;

					GM->PlayerDeathLogic(FVector(0, 0, 0), 1);

					bIsAttack = true;
				}
			}

			return;
		}
	}

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	if (bIsPlayerInRoom)
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
		SpawnLocation += FVector(0, 0, 88.0f);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (SpawnClass)
	{
		if (SpawnClass == HideAndSeekerClass)
		{
			SpawnedHideAndSeeker = GetWorld()->SpawnActor<ALB_MonsterHideAndSeeker>(SpawnClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (SpawnedHideAndSeeker)
			{

				SpawnedHideAndSeeker->SetOwner(this);

				if (CheckNearbyDoorOpened())
				{
					SpawnedHideAndSeeker->StartLogic_DoorOpen();

					GM->ResetKnockCount();
					GM->AddHelloCount();

					SpawnedHideAndSeeker->Sanity_Reduces(4.0f, this);
				}
				else
				{
					SpawnedHideAndSeeker->StartLogic_DoorClose();

					GM->ResetHelloCount();
					GM->AddKnockCount();

					SpawnedHideAndSeeker->Sanity_Reduces(2.0f, this);
				}
			}
		}
		
		/*if (SpawnClass == ChainSawManClass)
		{
			SpawnedChainSawMan = GetWorld()->SpawnActor<ALB_Monster_ChainSawMan>(SpawnClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (SpawnedChainSawMan)
			{
				SpawnedChainSawMan->SetOwner(this);

			}
		}*/
	}
}

bool ALB_TargetPoint_HAS::CheckNearbyDoorOpened()
{
	UWorld* World = GetWorld();
	if (!World) return true;

	FVector Start = GetActorLocation();
	FVector End = Start;
	float Radius = 200.f;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(this);

	TArray<FHitResult> HitResults;

	bool bHit = World->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_WorldDynamic, 
		Sphere,
		Params
	);

	if (!bHit) return true;

	ALB_LockDoor* Door = nullptr;
	float MinDist = 1000.0f;

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || !HitActor->ActorHasTag("Door")) continue;

		float DoorDistance = FVector::Dist(GetActorLocation(), HitActor->GetActorLocation());
		if (DoorDistance < MinDist)
		{
			MinDist = DoorDistance;

			Door = Cast<ALB_LockDoor>(Hit.GetActor());
		}
	}

	if (Door)
	{
		if (Door->bIsOpen)
		{
			return true;
		}
		else
		{
			ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
			if (!GM) return false;

			if (GM->GetShouldOpenDoor())
			{
				Door->OnWalkerBeginOverlap();
			}

			return false;
		}
	}

	return false;
}
