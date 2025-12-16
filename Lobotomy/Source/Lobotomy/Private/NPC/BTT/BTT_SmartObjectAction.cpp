// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_SmartObjectAction.h"
#include "AIController.h"

UBTT_SmartObjectAction::UBTT_SmartObjectAction()
{
	NodeName = TEXT("Smart Object Action");
}

EBTNodeResult::Type UBTT_SmartObjectAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	//ALB_Monster_Manequin* Monster_Manequin = Cast<ALB_Monster_Manequin>(ControlledPawn);
	//if (!Monster_Manequin) return EBTNodeResult::Failed;

	//Monster_Manequin->Manequin_Awake()

	return EBTNodeResult::Succeeded;
}
