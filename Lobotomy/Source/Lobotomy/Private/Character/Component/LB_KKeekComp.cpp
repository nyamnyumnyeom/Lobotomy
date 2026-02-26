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

		if (KKeek_Ref)
		{
			KKeek_Ref->KKeekKKeekVisible(CanActiveLocation);
		}

		WaitingTimer();

		CurrentSpawn_Length = CurrentSpawn_Length - Spawn_Length_Closer;
	}
}

void ULB_KKeekComp::DissapearKKeek()
{
	if (KKeek_Ref)
	{
		KKeek_Ref->KKeekKKeekInvisible();
	}
}

bool ULB_KKeekComp::CheckCanActive()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return false;

	FVector PlayerLocation = Player->GetActorLocation();

	FRotator YawOnlyRot(0.f, CamRot.Yaw, 0.f);
	FVector ForwardDir = YawOnlyRot.Vector();

	FVector TargetLocation = PlayerLocation + ForwardDir * CurrentSpawn_Length;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	FNavLocation Projected;
	if (NavSys && NavSys->ProjectPointToNavigation(TargetLocation, Projected))
	{
		TargetLocation = Projected.Location;
	}

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

void ULB_KKeekComp::CheckCanDissapear()
{
	if (!KKeek_Ref) return;

	ACharacter* Char = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Char) return;

	FVector PlayerForward = Char->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (KKeek_Ref->GetActorLocation() - Char->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	bIsTooFar = false;

	FVector Dist = KKeek_Ref->GetActorLocation() - Char->GetActorLocation();

	if (Dist.Length() > 1000.0f)
	{
		bIsTooFar = true;

		CheckCanDissapearBP();

		DissapearCheckTimerClear();

		return;
	}

	if (Dot >= Threshold)
	{
		CheckCanDissapearBP();

		DissapearCheckTimerClear();

		return;
	}

}

void ULB_KKeekComp::DissapearCheckTimerStart()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(DissapearTimerHandle, this, &ULB_KKeekComp::CheckCanDissapear, 0.1f, true);
	}
}

void ULB_KKeekComp::DissapearCheckTimerClear()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DissapearTimerHandle);
	}
}

void ULB_KKeekComp::TriggerLoopTimerStart()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TriggerLoopTimerHandle, this, &ULB_KKeekComp::CheakKKeekCondition, 1.0f, true);
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
		GetWorld()->GetTimerManager().SetTimer(WaitingTimerHandle, this, &ULB_KKeekComp::SetWaitingFalse, Action_WaitTime, false);
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

