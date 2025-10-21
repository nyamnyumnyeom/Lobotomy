// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_SpeedSetting.h"
#include "AIController.h"
#include "NPC/Interface/LB_Interface_MonsterState.h"

UBTT_SpeedSetting::UBTT_SpeedSetting()
{
	NodeName = TEXT("Checking Chase Mode");
}

EBTNodeResult::Type UBTT_SpeedSetting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	if (ControlledPawn->Implements<UCheakingState>())
	{
		//ICheakingState::Execute_CheckIsChase(ControlledPawn);

		return::EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
