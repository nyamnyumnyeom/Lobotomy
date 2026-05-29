// Fill out your copyright notice in the Description page of Project Settings.


#include "SurpriseActor/LB_DrawerSlot.h"
#include "LevelActor/LB_SurpriseBox.h"
#include "Components/BillboardComponent.h"

ALB_DrawerSlot::ALB_DrawerSlot()
{
	PrimaryActorTick.bCanEverTick = false;

	DrawerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrawerMesh"));
	SetRootComponent(DrawerMeshComponent);

	DrawerMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	SpawnBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SpawnBillboard->SetupAttachment(DrawerMeshComponent);

	Tags.Add(FName("SurpriseBoxPoint"));
}

// Called when the game starts or when spawned
void ALB_DrawerSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALB_DrawerSlot::SpawnSurpriseBox()
{
	if (SpawnedSurpriseBox != nullptr) return;

	int32 SpawnChance = FMath::RandRange(0, 100);
	if (SpawnChance > SpawnProbability) return;

	FVector SpawnLocation = SpawnBillboard->GetComponentLocation();
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (SurpriseBoxClass)
	{
		SpawnedSurpriseBox = GetWorld()->SpawnActor<ALB_SurpriseBox>(SurpriseBoxClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (SpawnedSurpriseBox)
		{
			bIsBoxSpawned = true;
			SpawnedSurpriseBox->SetOwner(this);
			SpawnedSurpriseBox->AttachToComponent(DrawerMeshComponent, FAttachmentTransformRules::KeepWorldTransform);

			bool SurpriseMode = false;
			int32 RandomValue = FMath::RandRange(0, 100);
			if (RandomValue < SurpriseProbability)
			{
				SurpriseMode = true;
				bIsSurpriseDelay = true;
			}

			SpawnedSurpriseBox->bIsSurprise = SurpriseMode;

		}
	}
}

void ALB_DrawerSlot::DespawnSurpriseBox()
{
	if (SpawnedSurpriseBox == nullptr) return;

	bIsBoxSpawned = false;
	SpawnedSurpriseBox->DespawnBattery();
	SpawnedSurpriseBox->Destroy();
	SpawnedSurpriseBox = nullptr;
}

