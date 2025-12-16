// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_ChangeNurseState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_ChangeNurseState::UBTT_ChangeNurseState()
{
	NodeName = TEXT("Change NPC State");
}

EBTNodeResult::Type UBTT_ChangeNurseState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(NewState));

	return EBTNodeResult::Succeeded;
}
