// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICMonsterDoctor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

ALB_AICMonsterDoctor::ALB_AICMonsterDoctor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALB_AICMonsterDoctor::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (bIsRuntimeSpawn)
	{
		SetBB_Target();
	}
	else
	{
		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SetBBTargetTimerHandle, this, &ALB_AICMonsterBase::SetBB_Target, 1.0f, false);
		}
	}
}
