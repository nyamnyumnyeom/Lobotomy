// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActor/LB_TargetPoint_SurpriseBox.h"
#include "LevelActor/LB_SurpriseBox.h"

ALB_TargetPoint_SurpriseBox::ALB_TargetPoint_SurpriseBox()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("SurpriseBoxPoint"));

}

void ALB_TargetPoint_SurpriseBox::BeginPlay()
{
	Super::BeginPlay();

}

void ALB_TargetPoint_SurpriseBox::SpawnSurpriseBox()
{
	if (SpawnedSurpriseBox != nullptr) return;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (SurpriseBoxClass)
	{
		SpawnedSurpriseBox = GetWorld()->SpawnActor<ALB_SurpriseBox>(SurpriseBoxClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (SpawnedSurpriseBox)
		{
			SpawnedSurpriseBox->SetOwner(this);

			bool SurpriseMode = true;

			int32 RandomValue = FMath::RandRange(0, 100);
			if (RandomValue > SurpriseProbability)
			{
				SurpriseMode = false;
			}

			SpawnedSurpriseBox->bIsSurprise = SurpriseMode;
		}
	}
}

void ALB_TargetPoint_SurpriseBox::DespawnSurpriseBox()
{
	if (SpawnedSurpriseBox == nullptr) return;

	SpawnedSurpriseBox->DespawnBattery();
	SpawnedSurpriseBox->Destroy();
	SpawnedSurpriseBox = nullptr;
}
