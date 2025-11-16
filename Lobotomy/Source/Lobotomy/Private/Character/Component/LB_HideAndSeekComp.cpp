// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/LB_HideAndSeekComp.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NPC/LB_TargetPoint_HAS.h"

ULB_HideAndSeekComp::ULB_HideAndSeekComp()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void ULB_HideAndSeekComp::BeginPlay()
{
	Super::BeginPlay();

}

void ULB_HideAndSeekComp::TriggerHASSpawn()
{
	ALB_TargetPoint_HAS* NearestHASPoint = FindNearestHAS();
	if (NearestHASPoint)
	{
		NearestHASPoint->HASSystemActivate(bIsPlayerInRoom);
	}
	else
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TriggerLoopTimerHandle, this, &ULB_HideAndSeekComp::TriggerHASSpawn, 1.0f, false);
		}
	}
}

ALB_TargetPoint_HAS* ULB_HideAndSeekComp::FindNearestHAS()
{
	AActor* MyPlayer = GetOwner();
	if (!MyPlayer) return nullptr;

	UWorld* World = MyPlayer->GetWorld();
	if (!World) return nullptr;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (!NavSys) return nullptr;

	FVector Start = MyPlayer->GetActorLocation();

	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(SearchRadius);

	bool bHit = World->SweepMultiByChannel(
		HitResults,
		Start,
		Start,
		FQuat::Identity,
		ECC_WorldDynamic,
		Sphere
	);

	if (bHit)
	{
		ALB_TargetPoint_HAS* NearestTarget = nullptr;

		float MinDist = FLT_MAX;

		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->ActorHasTag("HideAndSeekPoint"))
			{
				NearestTarget = Cast<ALB_TargetPoint_HAS>(HitActor);

				UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(World, Start, HitActor->GetActorLocation());

				if (NavPath && NavPath->IsValid() && NavPath->PathPoints.Num() > 1)
				{
					float PathLen = 0.f;
					for (int32 i = 1; i < NavPath->PathPoints.Num(); i++)
					{
						PathLen += FVector::Dist(NavPath->PathPoints[i - 1], NavPath->PathPoints[i]);
					}

					if (PathLen < MinDist)
					{
						MinDist = PathLen;
					}
				}
			}
		}

		if (NearestTarget)
		{
			return NearestTarget;
		}
	}

	return nullptr;
}


