// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/LB_KKeekComp.h"
#include "NPC/LB_Monster_KKeek.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "LB_GM.h"
#include "Character/LB_Character.h"
#include "Components/ShapeComponent.h"
#include "Engine/OverlapResult.h"

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

		ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (!GM) return;

		int32 MyCurrentDay = GM->CurrentDay;

		CurrentSpawn_Length = CurrentSpawn_Length - (Spawn_Length_Closer * MyCurrentDay);
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
	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return false;

	if (GM->bIsPlayerInRoom) return false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	ALB_Character* LB_Character = Cast<ALB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!LB_Character) return false;

	FProperty* Property = LB_Character->GetClass()->FindPropertyByName(FName("Isin?"));
	if (Property)
	{
		FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property);
		if (BoolProperty)
		{
			bool bCurrentValue = BoolProperty->GetPropertyValue_InContainer(LB_Character);
			if (bCurrentValue) return false;
		}
	}

	FVector PlayerLocation = LB_Character->GetActorLocation();

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
	Params.AddIgnoredActor(LB_Character);

	bool bBlocked = GetWorld()->LineTraceSingleByChannel(
		Hit,
		PlayerLocation,
		TargetLocation,
		ECC_Visibility,
		Params
	);

	if (bBlocked) return false;

	float ScanRadius = 1.0f;

	FCollisionQueryParams QueryParams(TEXT("RoomCheckQuery"));
	QueryParams.bTraceComplex = false; 

	TArray<FOverlapResult> OverlapResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	bool bHasOverlap = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		TargetLocation,
		FQuat::Identity,
		ObjectQueryParams, 
		FCollisionShape::MakeSphere(ScanRadius),
		QueryParams
	);

	if (bHasOverlap)
	{

		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, TEXT("월드 다이나믹이 무언가 걸리긴 했다네~"));

		for (const FOverlapResult& Result : OverlapResults)
		{
			AActor* OverlappedActor = Result.GetActor();

			if (OverlappedActor)
			{

				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, FString::Printf(TEXT("월드 다이나믹이 무언가 걸리긴 했다네~ : %s"), *OverlappedActor->GetName()));

				if (OverlappedActor->ActorHasTag(TEXT("RoomChecker")))
				{

					//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("스폰 포인트가 룸체크에 걸렸네~"));

					return false;
				}
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("아무것도 안걸렸다네"));

	CanActiveLocation = TargetLocation + FVector(0.0f, 0.0f, 90.0f);

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

	if (Dist.Length() > 1000.0f || Dist.Length() < 200.0f)
	{
		bIsTooFar = true;

		CheckCanDissapearBP();

		//DissapearCheckTimerClear();

		return;
	}

	if (Dot >= Threshold)
	{
		CheckCanDissapearBP();

		//DissapearCheckTimerClear();

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

void ULB_KKeekComp::DistanceReset()
{
	CurrentSpawn_Length = FirstSpawn_Length;
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

