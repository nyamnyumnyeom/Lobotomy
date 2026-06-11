// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/LB_HideAndSeekComp.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NPC/LB_TargetPoint_HAS.h"
#include "LB_GM.h"

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
	if (bIsSpawnDisable) return;

	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;

	if (GM->bIsNight == false) return;

	ALB_TargetPoint_HAS* NearestHASPoint = FindNearestHAS();
	if (NearestHASPoint)
	{
		AActor* MyPlayer = GetOwner();
		if (!MyPlayer) return;

		FVector PlayerForward = MyPlayer->GetActorForwardVector().GetSafeNormal();
		FVector ToPlayer = (NearestHASPoint->GetActorLocation() - MyPlayer->GetActorLocation()).GetSafeNormal();

		float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

		if (Dot <= Threshold)
		{
			NearestHASPoint->HASSystemActivate(bIsPlayerInRoom);

			GM->PlayerIntoRoom();

			return;
		}
	}

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TriggerLoopTimerHandle, this, &ULB_HideAndSeekComp::TriggerHASSpawn, 1.0f, false);
	}
}

void ULB_HideAndSeekComp::TriggerLoopTimerClear()
{
	GetWorld()->GetTimerManager().ClearTimer(TriggerLoopTimerHandle);
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

	if (!bHit) return nullptr;

	ALB_TargetPoint_HAS* NearestTarget = nullptr;
	float MinDist = PathLimit;

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || !HitActor->ActorHasTag("HideAndSeekPoint"))
			continue;

		UNavigationPath* NavPath =
			NavSys->FindPathToLocationSynchronously(World, Start, HitActor->GetActorLocation());

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

				ALB_TargetPoint_HAS* Target = Cast<ALB_TargetPoint_HAS>(HitActor);
				NearestTarget = Target;
			}
		}
	}

	return NearestTarget;
}


