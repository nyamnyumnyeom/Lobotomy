// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActor/LB_TargetPoint_TeddyBear.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "LevelActor/LB_TeddyBear.h"

ALB_TargetPoint_TeddyBear::ALB_TargetPoint_TeddyBear()
{
	PrimaryActorTick.bCanEverTick = false;

	LampMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LampMesh"));
	LampMeshComponent->SetupAttachment(RootComponent);

	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComponent->SetupAttachment(LampMeshComponent);
	SpotLightComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	DayIntensity = 5000.0f;
	NightIntensity = 10.0f;

	Tags.Add(FName("TeddyBearPoint"));
}

void ALB_TargetPoint_TeddyBear::BeginPlay()
{
	Super::BeginPlay();

	if (SpotLightComponent)
	{
		SpotLightComponent->SetIntensity(DayIntensity);
	}
}

void ALB_TargetPoint_TeddyBear::TriggerLightEffect(bool bIsNight)
{
	if (!SpotLightComponent) return;

	if (bIsNight)
	{
		SpotLightComponent->SetIntensity(NightIntensity);
	}
	else
	{
		SpotLightComponent->SetIntensity(DayIntensity);
	}

}

void ALB_TargetPoint_TeddyBear::ShowTeddyBear()
{
	if (!TeddyBear_Ref) return;

	if (!bIsBearHere) return;

	TeddyBear_Ref->SetBearActive(true);

	OnTeddyBearShow();
}

void ALB_TargetPoint_TeddyBear::ReferenceResister(ALB_TeddyBear* TeddyBearClass)
{
	if (!TeddyBearClass) return;

	TeddyBear_Ref = TeddyBearClass;
	bIsBearHere = true;
}

void ALB_TargetPoint_TeddyBear::ReferenceClear()
{
	TeddyBear_Ref = nullptr;
	bIsBearHere = false;
}
