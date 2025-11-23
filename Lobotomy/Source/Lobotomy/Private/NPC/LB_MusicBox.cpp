// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_MusicBox.h"
#include "Components/AudioComponent.h"
#include "NPC/LB_TargetPoint_MusicBox.h"

ALB_MusicBox::ALB_MusicBox()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;
}

void ALB_MusicBox::BeginPlay()
{
	Super::BeginPlay();

	int32 RandomIndex = FMath::RandRange(0, MusicSounds.Num() - 1);
	if (MusicSounds[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(MusicSounds[RandomIndex]);
		AudioComp->Play();
	}

	GetWorldTimerManager().SetTimer(
		NoiseTimerHandle,
		this,
		&ALB_MusicBox::MusicOff,
		DestroyTime,
		false
	);

	GetWorldTimerManager().SetTimer(
		NoiseTimerHandle,
		this,
		&ALB_MusicBox::MakeNoiseForAI,
		1.0f,    
		true  
	);
}

void ALB_MusicBox::MusicOff()
{
	if (ALB_TargetPoint_MusicBox* OwnerTargetPoint = Cast<ALB_TargetPoint_MusicBox>(GetOwner()))
	{
		OwnerTargetPoint->StopMusicBoxTimer();
	}

	if (AudioComp)
	{
		AudioComp->Stop();
	}
}

