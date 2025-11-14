// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICBase.h"
#include "BehaviorTree/BehaviorTree.h"

ALB_AICBase::ALB_AICBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALB_AICBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BT && UseBlackboard(BT->BlackboardAsset, BB))
	{
		RunBehaviorTree(BT);
	}
}
