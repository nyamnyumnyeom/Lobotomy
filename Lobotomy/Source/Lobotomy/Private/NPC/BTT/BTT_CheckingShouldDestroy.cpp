// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_CheckingShouldDestroy.h"
#include "AIController.h"
#include "NPC/Interface/LB_Interface_MonsterState.h"

UBTT_CheckingShouldDestroy::UBTT_CheckingShouldDestroy()
{
	NodeName = TEXT("Checking Should Destroy");
}

EBTNodeResult::Type UBTT_CheckingShouldDestroy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	if (ControlledPawn->Implements<UCheakingState>())
	{
		ICheakingState::Execute_CheakShouldDestroy(ControlledPawn);

		return::EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
