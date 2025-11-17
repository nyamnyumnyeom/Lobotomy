// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_MonsterHideAndSeeker.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"

ALB_MonsterHideAndSeeker::ALB_MonsterHideAndSeeker()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerDetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectSphere"));
	PlayerDetectSphere->SetupAttachment(RootComponent);

	PlayerDetectSphere->InitSphereRadius(300.f);
	PlayerDetectSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlayerDetectSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	PlayerDetectSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerDetectSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PlayerDetectSphere->OnComponentBeginOverlap.AddDynamic(this, &ALB_MonsterHideAndSeeker::OnSphereBeginOverlap);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;
}

void ALB_MonsterHideAndSeeker::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	int32 RandomIndex = FMath::RandRange(0, KnockSounds.Num() - 1);
	if (KnockSounds[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(KnockSounds[RandomIndex]);
		AudioComp->Play();
	}

	GetWorldTimerManager().SetTimer(BeginPlayTimerHandle, this, &ALB_MonsterHideAndSeeker::StartRandomSideMove, 10.0f, false);
}

void ALB_MonsterHideAndSeeker::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->ActorHasTag("Player"))
	{
		StartRandomSideMove();
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
	if (bIsMovingSideways) return;

	bIsMovingSideways = true;

	GetWorldTimerManager().ClearTimer(BeginPlayTimerHandle);

	float RandomSide = FMath::RandBool() ? 1.0f : -1.0f;

	MoveDirection = GetActorRightVector() * RandomSide;

	GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ALB_MonsterHideAndSeeker::StopRandomSideMove, MoveDuration, false);

	int32 RandomIndex = FMath::RandRange(0, KnockSounds.Num() - 1);
	if (KnockSounds[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(KnockSounds[RandomIndex]);
		AudioComp->Play();
	}
}

void ALB_MonsterHideAndSeeker::StopRandomSideMove()
{
	bIsMovingSideways = false;
	MoveDirection = FVector::ZeroVector;

	int32 RandomIndex = FMath::RandRange(0, LaghingSounds.Num() - 1);
	if (LaghingSounds[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(LaghingSounds[RandomIndex]);
		AudioComp->Play();
	}

	Destroy();
}
