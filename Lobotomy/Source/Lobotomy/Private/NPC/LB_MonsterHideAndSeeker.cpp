// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_MonsterHideAndSeeker.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"

ALB_MonsterHideAndSeeker::ALB_MonsterHideAndSeeker()
{
	PrimaryActorTick.bCanEverTick = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;
}

void ALB_MonsterHideAndSeeker::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (MusicSound && AudioComp)
	{
		AudioComp->SetSound(MusicSound);
		AudioComp->Play();
	}
}

void ALB_MonsterHideAndSeeker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter)
	{
		FVector PlayerForward = PlayerCharacter->GetActorForwardVector().GetSafeNormal();

		FVector ToPlayer = (GetActorLocation() - PlayerCharacter->GetActorLocation()).GetSafeNormal();

		float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

		if (!bIsMovingSideways)
		{
			if (Dot >= Threshold)
			{
				StartRandomSideMove();
			}
		}
		else if (bIsMovingSideways)
		{
			AddMovementInput(MoveDirection, MoveSpeed);
		}
	}
}

void ALB_MonsterHideAndSeeker::StartRandomSideMove()
{
	bIsMovingSideways = true;

	float RandomSide = FMath::RandBool() ? 1.0f : -1.0f;

	MoveDirection = GetActorRightVector() * RandomSide;

	GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ALB_MonsterHideAndSeeker::StopRandomSideMove, MoveDuration, false);
}

void ALB_MonsterHideAndSeeker::StopRandomSideMove()
{
	bIsMovingSideways = false;
	MoveDirection = FVector::ZeroVector;

	Destroy();
}
