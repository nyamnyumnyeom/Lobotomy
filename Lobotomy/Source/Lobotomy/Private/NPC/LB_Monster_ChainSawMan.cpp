// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_ChainSawMan.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"
#include "Components/SphereComponent.h"
#include "NPC/AI/LB_AICMonster_ChainSawMan.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/LB_NPCData.h"
#include "Components/AudioComponent.h"
#include "Character/LB_Character.h"

ALB_Monster_ChainSawMan::ALB_Monster_ChainSawMan()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(180.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALB_Monster_ChainSawMan::OnOverlapBegin);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;
}

void ALB_Monster_ChainSawMan::BeginPlay()
{
	Super::BeginPlay();

	SpawnLogic();

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(SpeedSettingTimerHandle, this, &ALB_Monster_ChainSawMan::SpeedSettingTimer, 2.0f, true);
		GetWorldTimerManager().SetTimer(SanityTimerHandle, this, &ALB_Monster_ChainSawMan::SanityTimer, 1.0f, true);
	}

	HeartbeatToggle(true);
}

void ALB_Monster_ChainSawMan::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			if (CheakPlayerIsIn()) return;

			ALB_AICMonster_ChainSawMan* AIC = Cast<ALB_AICMonster_ChainSawMan>(GetController());
			if (AIC)
			{
				OnWeaponUp();

				HeartbeatToggle(false);

				CachedPlayerCharacter = OtherActor;
				AIC->SetState_Attack();

				if (AudioComp && AudioComp->IsPlaying())
				{
					AudioComp->Stop();
				}

				int32 RandomIndex = FMath::RandRange(0, FinishSounds.Num() - 1);
				if (FinishSounds[RandomIndex] && AudioComp)
				{
					AudioComp->SetSound(FinishSounds[RandomIndex]);
					AudioComp->Play();
				}

			}
		}
	}
}

bool ALB_Monster_ChainSawMan::CheakShouldDestroy_Implementation()
{
	if (!bIsSpawnDurationOver) return false;

	APawn* TargetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerForward = TargetActor->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (GetActorLocation() - TargetActor->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	if (CheakPlayerIsIn())
	{
		DisappearLogic();

		return true;
	}

	if (Dot <= 0)
	{
		DisappearLogic();

		return true;
	}

	return false;
}

void ALB_Monster_ChainSawMan::CheckIsChase_Implementation(bool bIsChase)
{
	bIsChasing = bIsChase;
}

void ALB_Monster_ChainSawMan::SpawnLogic()
{
	SetSpawnWhetherToGM(true);

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnDurationTimerHandle);
		GetWorldTimerManager().SetTimer(SpawnDurationTimerHandle, this, &ALB_Monster_ChainSawMan::TimeupSpawnDuration, SpawnDuration, false);
	}

	int32 RandomIndex = FMath::RandRange(0, SpawnSounds.Num() - 1);
	if (SpawnSounds[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(SpawnSounds[RandomIndex]);
		AudioComp->Play();
	}

	GetWorldTimerManager().SetTimer(SoundPlayTimerHandle, this, &ALB_Monster_ChainSawMan::SoundPlay, SoundPlayDelay, true);
}

void ALB_Monster_ChainSawMan::SetActorRotationToPlayer()
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

void ALB_Monster_ChainSawMan::DisappearLogic()
{
	SetSpawnWhetherToGM(false);

	GetWorldTimerManager().ClearTimer(SoundPlayTimerHandle);
	GetWorldTimerManager().ClearTimer(SanityTimerHandle);

	if (AudioComp && AudioComp->IsPlaying())
	{
		AudioComp->Stop();
	}
	
	HeartbeatToggle(false);

	if (Owner)
	{
		Owner->Destroy();
	}

	Destroy();
}

void ALB_Monster_ChainSawMan::SetSpawnWhetherToGM(bool Value)
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->SetIsChainSawManSpawned(Value);
		if (Value)
		{
			GM->SetChainSawManRef(this);
		}
		else
		{
			GM->SetChainSawManRef(nullptr);
		}
	}
}

void ALB_Monster_ChainSawMan::TimeupSpawnDuration()
{
	bIsSpawnDurationOver = true;
}

void ALB_Monster_ChainSawMan::SpeedSettingTimer()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if (!AICon) return;

	UBlackboardComponent* BBComp = AICon->GetBlackboardComponent();
	if (!BBComp) return;

	uint8 CurrentState = BBComp->GetValueAsEnum(TEXT("CurrentState"));
	if (CurrentState)
	{
		EMonsterState State = static_cast<EMonsterState>(CurrentState);
		if (State == EMonsterState::Chase)
		{
			bIsChasing = true;
		}
		else
		{
			bIsChasing = false;
		}
	}

	if (!bIsChasing)
	{
		CurrentSpeed = DefaultSpeed;
		SpeedApply();
		return;
	}

	if (bIsRunning) return;

	int32 Rand = FMath::RandRange(1, 100);
	if (Rand <= 10)
	{
		bIsRunning = true;
		CurrentSpeed = DashSpeed;
		SpeedApply();

		if (GetWorld())
		{
			GetWorldTimerManager().ClearTimer(RunModeTimerHandle);

			int32 DashTime = FMath::RandRange(5, 10);
			GetWorldTimerManager().SetTimer(RunModeTimerHandle, this, &ALB_Monster_ChainSawMan::SpeedReset, DashTime, false);
		}
	}

}

void ALB_Monster_ChainSawMan::SpeedApply()
{
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}

void ALB_Monster_ChainSawMan::SpeedReset()
{
	bIsRunning = false;
	CurrentSpeed = DefaultSpeed;
	SpeedApply();
}

void ALB_Monster_ChainSawMan::SoundPlay()
{
	if (AudioComp && AudioComp->IsPlaying()) return;

	int32 RandomIndex = FMath::RandRange(0, NormalSounds.Num() - 1);
	if (NormalSounds[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(NormalSounds[RandomIndex]);
		AudioComp->Play();
	}
}

void ALB_Monster_ChainSawMan::HeartbeatToggle(bool Value)
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

void ALB_Monster_ChainSawMan::SanityTimer()
{
	Sanity_Reduces(0.1f);
}
