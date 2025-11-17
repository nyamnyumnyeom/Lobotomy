// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/TargetPoint_Patient.h"
#include "NPC/LB_PatientBase.h"

ATargetPoint_Patient::ATargetPoint_Patient()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("HideAndSeekPoint"));
}

void ATargetPoint_Patient::BeginPlay()
{
	Super::BeginPlay();

	SpawnLogic(PatientClass);
}

void ATargetPoint_Patient::``(TSubclassOf<AActor> SpawnClass)
{
	if (!SpawnClass) return;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	FVector Start = SpawnLocation;
	FVector End = Start - FVector(0, 0, 300.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		SpawnLocation = HitResult.ImpactPoint;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnLocation += FVector(0, 0, upscale);

	SpawnedPatient = GetWorld()->SpawnActor<ALB_PatientBase>(SpawnClass, SpawnLocation, SpawnRotation, SpawnParams);
	SpawnedPatient->BehaviorMode = BehaviorModeChoose;
}
