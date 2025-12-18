// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActor/LB_TargetPoint_TeddyBear.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "LevelActor/LB_TeddyBear.h"
#include "NPC/LB_Monster_TeddyBear.h"
#include "LB_GM.h"
#include "Kismet/GameplayStatics.h"

ALB_TargetPoint_TeddyBear::ALB_TargetPoint_TeddyBear()
{
	PrimaryActorTick.bCanEverTick = false;

	LampMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LampMesh"));
	LampMeshComponent->SetupAttachment(RootComponent);

	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComponent->SetupAttachment(LampMeshComponent);
	SpotLightComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	MonsterSpawnBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	MonsterSpawnBillboard->SetupAttachment(RootComponent);
	MonsterSpawnBillboard->SetRelativeLocation(FVector(200.0f, 0.0f, 0.0f));
	MonsterSpawnBillboard->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	MonsterSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("InsideSpawnPoint"));
	MonsterSpawnPoint->SetupAttachment(MonsterSpawnBillboard);

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

	OnTeddyBearShow();
}

void ALB_TargetPoint_TeddyBear::InteractWidgetHide()
{
	if (!TeddyBear_Ref) return;

	TeddyBear_Ref->OnInteractWidgetHide();
}

void ALB_TargetPoint_TeddyBear::TeddyBearSetVisibility(bool Visibility)
{
	if (!TeddyBear_Ref) return;

	TeddyBear_Ref->SetBearVisibility(Visibility);
}

void ALB_TargetPoint_TeddyBear::TeddyBearSetActiveCollision(bool Collision)
{
	if (!TeddyBear_Ref) return;

	TeddyBear_Ref->SetBearCollision(Collision);
}

void ALB_TargetPoint_TeddyBear::SpawnMonsterBear()
{
	FVector SpawnLocation = MonsterSpawnBillboard->GetComponentLocation();
	FRotator SpawnRotation = MonsterSpawnBillboard->GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	MonsterBear_Ref = GetWorld()->SpawnActor<ALB_Monster_TeddyBear>(MonsterBearClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (MonsterBear_Ref)
	{
		MonsterBear_Ref->SetOwner(this);

	}
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

void ALB_TargetPoint_TeddyBear::GetBearHere()
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;

	ALB_TeddyBear* NewTeddy = GM->GetTeddyRef();
	if (!NewTeddy) return;

	ReferenceResister(NewTeddy);

	NewTeddy->SetBearVisibility(false);
	NewTeddy->SetBearCollision(false);
	NewTeddy->bIsCheckTonight = false;
	NewTeddy->TeleportToSpecialTarget(this);

}

//bool ALB_TargetPoint_TeddyBear::GetbIsBearHere()
//{
//	return bIsBearHere;
//}
