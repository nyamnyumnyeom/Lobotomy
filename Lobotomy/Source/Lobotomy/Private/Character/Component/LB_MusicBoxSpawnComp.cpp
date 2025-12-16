// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/LB_MusicBoxSpawnComp.h"
#include "NPC/LB_TargetPoint_MusicBox.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"

ULB_MusicBoxSpawnComp::ULB_MusicBoxSpawnComp()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULB_MusicBoxSpawnComp::BeginPlay()
{
	Super::BeginPlay();

}

void ULB_MusicBoxSpawnComp::TriggerMusicBoxSpawn()
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;

	if (GM->bIsNight == false) return;

	AActor* MyOwnerPawn = GetOwner();
	if (!MyOwnerPawn) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector Start = MyOwnerPawn->GetActorLocation();
	float Radius = SphereTraceRadius;

	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

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
		ALB_TargetPoint_MusicBox* NearestPoint = nullptr;
		float MinDist = FLT_MAX;

		AActor* NearestActor = nullptr;

		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->ActorHasTag("MusicBoxPoint"))
			{
				float PlayerHeight = MyOwnerPawn->GetActorLocation().Z;
				float TargetHeight = HitActor->GetActorLocation().Z;
				if (PlayerHeight - 200.0f > TargetHeight) continue;
				if (PlayerHeight + 200.0f < TargetHeight) continue;

				FVector PlayerForward = MyOwnerPawn->GetActorForwardVector().GetSafeNormal();
				FVector ToPlayer = (HitActor->GetActorLocation() - Start).GetSafeNormal();

				float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

				if (Dot <= Threshold)
				{
					float Dist = FVector::Dist(Start, HitActor->GetActorLocation());
					if (Dist < MinDist)
					{
						MinDist = Dist;
						NearestActor = HitActor;
					}
				}
			}
		}

		if (NearestActor)
		{
			NearestPoint = Cast<ALB_TargetPoint_MusicBox>(NearestActor);
			if (NearestPoint)
			{
				NearestPoint->MusicBoxSystemActivate();
				return;
			}
		}
	}

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TriggerLoopTimerHandle, this, &ULB_MusicBoxSpawnComp::TriggerMusicBoxSpawn, 10.0f, false);
	}
}

void ULB_MusicBoxSpawnComp::TriggerLoopTimerClear()
{
	GetWorld()->GetTimerManager().ClearTimer(TriggerLoopTimerHandle);
}