// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_TeddyBear.h"
#include "Kismet/GameplayStatics.h"
#include "LevelActor/LB_TargetPoint_TeddyBear.h"
#include "LevelActor/LB_TeddyBear.h"
#include "Character/Component/LB_TeddyBearComp.h"
#include "Character/LB_Character.h"
#include "LB_GM.h"
#include "Components/SphereComponent.h"
#include "NPC/AI/LB_AICMonster_TeddyBear.h"

ALB_Monster_TeddyBear::ALB_Monster_TeddyBear()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(180.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALB_Monster_TeddyBear::OnOverlapBegin);
}

bool ALB_Monster_TeddyBear::CheakShouldDestroy_Implementation()
{
	if (!bIsSpawnDurationOver) return false;

	APawn* TargetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerForward = TargetActor->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (GetActorLocation() - TargetActor->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	if (Dot <= 0)
	{
		DisappearLogic();

		return true;
	}

	return false;
}

void ALB_Monster_TeddyBear::DisappearLogic()
{
	ALB_TargetPoint_TeddyBear* OwnerTP = Cast<ALB_TargetPoint_TeddyBear>(GetOwner());
	if (OwnerTP)
	{
		OwnerTP->TeddyBear_Ref->bIsCheckTonight = false;
		//OwnerTP->TeddyBear_Ref->TeleportToRandomTarget();
		OwnerTP->TeddyBear_Ref->TeleportToOrigin();
	}

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerChar)
	{
		ULB_TeddyBearComp* FoundComp = PlayerChar->FindComponentByClass<ULB_TeddyBearComp>();
		if (FoundComp)
		{
			FoundComp->bIsChecked = false;
		}
	}

	SetSpawnWhetherToGM(false);

	Destroy();
}

void ALB_Monster_TeddyBear::SetActorRotationToPlayer()
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

void ALB_Monster_TeddyBear::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnDurationTimerHandle);
		GetWorldTimerManager().SetTimer(SpawnDurationTimerHandle, this, &ALB_Monster_TeddyBear::TimeupSpawnDuration, SpawnDuration, false);
	}

	SetSpawnWhetherToGM(true);

	PlaySound_Spawn();
}

void ALB_Monster_TeddyBear::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			ALB_AICMonster_TeddyBear* AIC = Cast<ALB_AICMonster_TeddyBear>(GetController());
			if (AIC)
			{
				CachedPlayerCharacter = OtherActor;
				AIC->SetState_Attack();
				PlaySound_Kill();
			}
		}
	}
}

void ALB_Monster_TeddyBear::TimeupSpawnDuration()
{
	bIsSpawnDurationOver = true;
}

void ALB_Monster_TeddyBear::SetSpawnWhetherToGM(bool Value)
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		//GM->SetIsChainSawManSpawned(Value);
		if (Value)
		{
			GM->SetTeddyBearRef(this);
		}
		else
		{
			GM->SetTeddyBearRef(nullptr);
		}
	}
}

void ALB_Monster_TeddyBear::PlaySound_Spawn()
{
	if (SpawnSoundCue)
	{
		UGameplayStatics::SpawnSoundAttached(
			SpawnSoundCue,
			GetRootComponent()
		);
	}
}

void ALB_Monster_TeddyBear::PlaySound_Kill()
{
	if (KillSoundCue)
	{
		UGameplayStatics::SpawnSoundAttached(
			KillSoundCue,
			GetRootComponent()
		);
	}
}

