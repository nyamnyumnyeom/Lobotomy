// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActor/LB_TeddyBear.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelActor/LB_TargetPoint_TeddyBear.h"


ALB_TeddyBear::ALB_TeddyBear()
{
	PrimaryActorTick.bCanEverTick = false;

	TeddyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeddyMesh"));
	TeddyMeshComponent->SetupAttachment(RootComponent);
	TeddyMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

void ALB_TeddyBear::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();
	OriginRotator = GetActorRotation();
}

void ALB_TeddyBear::CheckMonsterPercentage(bool& bShouldMonster)
{
	int32 RandomValue = FMath::RandRange(0, 100);
	if (RandomValue < MonsterPercentage)
	{
		bShouldMonster = true;
	}
	else
	{
		bShouldMonster = false;
	}
}

void ALB_TeddyBear::MonsterLightDirected()
{
	if (!TargetPoint_Ref) return;

	TargetPoint_Ref->OnMonsterBearShow();
}

void ALB_TeddyBear::SetBearVisibility(bool bIsActive)
{
	if (!TeddyMeshComponent) return;

	TeddyMeshComponent->SetVisibility(bIsActive, true);
}

void ALB_TeddyBear::SetBearCollision(bool bIsActive)
{
	if (!TeddyMeshComponent) return;

	if (bIsActive)
	{
		TeddyMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		TeddyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ALB_TeddyBear::TeleportToRandomTarget()
{
	ReferenceClear();

	TArray<AActor*> FoundPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALB_TargetPoint_TeddyBear::StaticClass(), FoundPoints);

	if (FoundPoints.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, FoundPoints.Num() - 1);

		AActor* TargetActor = FoundPoints[RandomIndex];

		if (TargetActor)
		{
			SetActorLocationAndRotation(TargetActor->GetActorLocation(), TargetActor->GetActorRotation());

			TargetPoint_Ref = Cast<ALB_TargetPoint_TeddyBear>(TargetActor);
			if (TargetPoint_Ref)
			{
				TargetPoint_Ref->ReferenceResister(this);
			}
		}
	}
}

void ALB_TeddyBear::TeleportToOrigin()
{
	SetActorLocationAndRotation(OriginLocation, OriginRotator);
}

void ALB_TeddyBear::ReferenceClear()
{
	if (TargetPoint_Ref)
	{
		TargetPoint_Ref->ReferenceClear();
	}
}

