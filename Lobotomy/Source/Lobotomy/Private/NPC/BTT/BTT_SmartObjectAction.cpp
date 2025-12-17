// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_SmartObjectAction.h"
#include "AIController.h"
#include "NPC/AI/LB_AIC_Nurse.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_SmartObjectAction::UBTT_SmartObjectAction()
{
	NodeName = TEXT("Smart Object Action");

	SOActionNumberKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_SmartObjectAction, SOActionNumberKey));
}

EBTNodeResult::Type UBTT_SmartObjectAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	ALB_AIC_Nurse* MyAIC = Cast<ALB_AIC_Nurse>(AIController);
	if(!MyAIC) return EBTNodeResult::Failed;

	/*UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	int32 SOActionNum = BB->GetValueAsInt(SOActionNumberKey.SelectedKeyName);*/

	MyAIC->SOAction_Start();

	return EBTNodeResult::Succeeded;
}
