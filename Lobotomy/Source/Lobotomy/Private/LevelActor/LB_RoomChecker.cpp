// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActor/LB_RoomChecker.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"
#include "Character/Component/LB_HideAndSeekComp.h"
#include "Character/Component/LB_MusicBoxSpawnComp.h"


ALB_RoomChecker::ALB_RoomChecker()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALB_RoomChecker::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ALB_RoomChecker::OnOverlapEnd);
}

void ALB_RoomChecker::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));

	GetWorldTimerManager().SetTimer(StartCheckTimerHandle, this, &ALB_RoomChecker::CheckPlayerOverlap, 2.0f, false);
}

void ALB_RoomChecker::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->ActorHasTag("Player"))
	{
		if (!GM) return;

		GM->PlayerIntoRoom();

		ULB_MusicBoxSpawnComp* MBComp = OtherActor->FindComponentByClass<ULB_MusicBoxSpawnComp>();
		if (MBComp)
		{
			MBComp->TriggerLoopTimerClear();
		}
	}
}

void ALB_RoomChecker::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	if (OtherActor->ActorHasTag("Player"))
	{
		if (!GM) return;
		
		GM->PlayerIntoLobby();

		ULB_HideAndSeekComp* HASComp = OtherActor->FindComponentByClass<ULB_HideAndSeekComp>();
		if (HASComp)
		{
			HASComp->TriggerLoopTimerClear();
		}
	}
}

void ALB_RoomChecker::CheckPlayerOverlap()
{
	TArray<AActor*> OverlappingActors;
	BoxCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			GM->PlayerIntoRoom();
			return;
		}
	}
}
