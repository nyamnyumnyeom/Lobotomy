// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_ChainSawMan.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"
#include "Components/SphereComponent.h"
#include "NPC/AI/LB_AICMonster_ChainSawMan.h"

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
}

void ALB_Monster_ChainSawMan::BeginPlay()
{
	Super::BeginPlay();

	SpawnLogic();
}

void ALB_Monster_ChainSawMan::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			ALB_AICMonster_ChainSawMan* AIC = Cast<ALB_AICMonster_ChainSawMan>(GetController());
			if (AIC)
			{
				OnWeaponUp();

				CachedPlayerCharacter = OtherActor;
				AIC->SetState_Attack();

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

	if (Dot <= 0)
	{
		DisappearLogic();

		return true;
	}

	return false;
}

void ALB_Monster_ChainSawMan::SpawnLogic()
{
	SetSpawnWhetherToGM(true);

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnDurationTimerHandle);
		GetWorldTimerManager().SetTimer(SpawnDurationTimerHandle, this, &ALB_Monster_ChainSawMan::TimeupSpawnDuration, SpawnDuration, false);
	}
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

	Destroy();
}

void ALB_Monster_ChainSawMan::SetSpawnWhetherToGM(bool Value)
{
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->SetIsChainSawManSpawned(Value);
	}
}

void ALB_Monster_ChainSawMan::TimeupSpawnDuration()
{
	bIsSpawnDurationOver = true;
}
