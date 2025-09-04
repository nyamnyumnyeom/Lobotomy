// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_Manequin_Awake.h"
#include "AIController.h"
#include "NPC/LB_Monster_Manequin.h"

UBTT_Manequin_Awake::UBTT_Manequin_Awake()
{
	NodeName = TEXT("Manequin Awake");
}

EBTNodeResult::Type UBTT_Manequin_Awake::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	ALB_Monster_Manequin* Monster_Manequin = Cast<ALB_Monster_Manequin>(ControlledPawn);
	if (!Monster_Manequin) return EBTNodeResult::Failed;

	Monster_Manequin->Manequin_Awake();

	return EBTNodeResult::Succeeded;
}
