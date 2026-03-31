// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_Doctor.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/AI/LB_AICMonsterDoctor.h"
#include "Components/AudioComponent.h"
#include "Character/LB_Character.h"

ALB_Monster_Doctor::ALB_Monster_Doctor()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(180.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALB_Monster_Doctor::OnOverlapBegin);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;
}

void ALB_Monster_Doctor::BeginPlay()
{
	Super::BeginPlay();

	SpawnLogic();

	HeartbeatToggle(true);
}

void ALB_Monster_Doctor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			ALB_AICMonsterDoctor* AIC = Cast<ALB_AICMonsterDoctor>(GetController());
			if (AIC)
			{
				OnWeaponUp();

				HeartbeatToggle(false);

				CachedPlayerCharacter = OtherActor;
				AIC->SetState_Attack();

				SoundPlay(2);

				SetActorRotationToPlayer();

				ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
				if (!GM) return;

				GM->PlayerDeathLogic(GetActorLocation(), 4);
			}
		}
	}
}

void ALB_Monster_Doctor::SpawnLogic()
{
	SoundPlay(0);

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(SoundPlayTimerHandle, [this](){SoundPlay(1);}, SoundPlayDelay, true);
	}

	ALB_AICMonsterDoctor* AIC = Cast<ALB_AICMonsterDoctor>(GetController());
	if (AIC)
	{
		AIC->SetFocusPlayer();
	}
}

void ALB_Monster_Doctor::SetActorRotationToPlayer()
{
	if (CachedPlayerCharacter)
	{
		FVector TargetLocation = CachedPlayerCharacter->GetActorLocation();
		FVector MyLocation = GetActorLocation();

		TargetLocation.Z = MyLocation.Z;

		FRotator LookAtRot = (TargetLocation - MyLocation).Rotation();
		SetActorRotation(LookAtRot);
	}
}

void ALB_Monster_Doctor::SoundPlay(int32 SoundType)
{
	if (AudioComp && AudioComp->IsPlaying())
	{
		AudioComp->Stop();
	}

	TArray<USoundBase*>* SelectedArray = nullptr;

	switch (SoundType)
	{
	case 0:
		SelectedArray = &SpawnSounds;
		break;

	case 1:
		SelectedArray = &NormalSounds;
		break;

	case 2:
		SelectedArray = &FinishSounds;
		break;

	default:
		return;
	}

	if (!SelectedArray || SelectedArray->Num() == 0) return;

	int32 RandomIndex = FMath::RandRange(0, SelectedArray->Num() - 1);

	if ((*SelectedArray)[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound((*SelectedArray)[RandomIndex]);
		AudioComp->Play();
	}
}

void ALB_Monster_Doctor::HeartbeatToggle(bool Value)
{
	ALB_Character* Player = Cast<ALB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		if (Value)
		{
			Player->SetHeartbeatTarget(this);
			Player->StartHeartbeat();
		}
		else
		{
			Player->ResetHeartbeatTarget();
			Player->StopHeartbeat();
		}
	}
}