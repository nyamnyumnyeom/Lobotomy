// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/LB_KKeekComp.h"
#include "NPC/LB_Monster_KKeek.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

ULB_KKeekComp::ULB_KKeekComp()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void ULB_KKeekComp::BeginPlay()
{
	Super::BeginPlay();

	
}

void ULB_KKeekComp::TriggerKKeek()
{
	if (bIsWaiting) return;
	if (bIsKKeekHere) return;

	if (CheckCanActive())
	{
		bIsWaiting = true;

		KKeek_Ref->KKeekKKeekVisible(CanActiveLocation);

		CurrentSpawn_Length = CurrentSpawn_Length - Spawn_Length_Closer;
	}
}

bool ULB_KKeekComp::CheckCanActive()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	FVector TargetLocation = CamLoc + CamRot.Vector() * CurrentSpawn_Length;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	FNavLocation Projected;
	if (!NavSys || !NavSys->ProjectPointToNavigation(TargetLocation, Projected))
	{
		return false;
	}

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return false;

	FVector PlayerLocation = Player->GetActorLocation();

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);

	bool bBlocked = GetWorld()->LineTraceSingleByChannel(
		Hit,
		PlayerLocation,
		TargetLocation,
		ECC_Visibility,
		Params
	);

	if (bBlocked) return false;

	CanActiveLocation = TargetLocation;

	return true;
}

void ULB_KKeekComp::TriggerLoopTimerStart()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TriggerLoopTimerHandle, this, &ULB_KKeekComp::TriggerKKeek, 1.0f, true);
	}
}

void ULB_KKeekComp::TriggerLoopTimerClear()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TriggerLoopTimerHandle);
	}
}

void ULB_KKeekComp::WaitingTimer()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TriggerLoopTimerHandle, this, &ULB_KKeekComp::SetWaitingFalse, Action_WaitTime, false);
	}
}

void ULB_KKeekComp::ResistKKeek(ALB_Monster_KKeek* Ref)
{
	if (Ref)
	{
		KKeek_Ref = Ref;
	}
}

void ULB_KKeekComp::SetWaitingFalse()
{
	bIsWaiting = false;
}

