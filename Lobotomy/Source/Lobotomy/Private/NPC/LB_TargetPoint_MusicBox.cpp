// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_TargetPoint_MusicBox.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/LB_MusicBox.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Character.h"

ALB_TargetPoint_MusicBox::ALB_TargetPoint_MusicBox()
{
	PrimaryActorTick.bCanEverTick = false;

	ChainSawManBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	ChainSawManBillboard->SetupAttachment(RootComponent);
	ChainSawManBillboard->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));

	ChainSawManSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ChainSawManSpawnPoint"));
	ChainSawManSpawnPoint->SetupAttachment(ChainSawManBillboard);

	Tags.Add(FName("MusicBoxPoint"));
}

void ALB_TargetPoint_MusicBox::BeginPlay()
{
	Super::BeginPlay();

}

void ALB_TargetPoint_MusicBox::MusicBoxSystemActivate()
{
	if (SpawnedMusicBox != nullptr) return;

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

	if (MusicBoxClass)
	{
		SpawnedMusicBox = GetWorld()->SpawnActor<ALB_MusicBox>(MusicBoxClass, SpawnLocation, SpawnRotation);
		if (SpawnedMusicBox)
		{
			SpawnedMusicBox->SetOwner(this);

			GetWorldTimerManager().SetTimer(MusicBoxTimerHandle, this, &ALB_TargetPoint_MusicBox::MusicBoxTimeup, 20.0f, false);
		}
	}
}

void ALB_TargetPoint_MusicBox::StopMusicBoxTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(MusicBoxTimerHandle);

	GetWorldTimerManager().SetTimer(MusicBoxDestroyTimerHandle, this, &ALB_TargetPoint_MusicBox::TryMusicBoxDestroy, 2.0f, true);

}

void ALB_TargetPoint_MusicBox::MusicBoxTimeup()
{
	if (ChainSawManClass && ChainSawManSpawnPoint)
    {
        FVector SpawnLocation = ChainSawManSpawnPoint->GetComponentLocation();
        FRotator SpawnRotation = ChainSawManSpawnPoint->GetComponentRotation();

        GetWorld()->SpawnActor<AActor>(ChainSawManClass, SpawnLocation, SpawnRotation);
    }
}

void ALB_TargetPoint_MusicBox::TryMusicBoxDestroy()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector PlayerForward = PlayerCharacter->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (GetActorLocation() - PlayerCharacter->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	if (Dot >= 0) return;

	SpawnedMusicBox->Destroy();

	GetWorld()->GetTimerManager().ClearTimer(MusicBoxDestroyTimerHandle);
}
