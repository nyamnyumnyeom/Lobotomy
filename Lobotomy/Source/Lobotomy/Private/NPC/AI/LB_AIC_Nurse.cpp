// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AIC_Nurse.h"
#include "BehaviorTree/BlackboardComponent.h"


ALB_AIC_Nurse::ALB_AIC_Nurse()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALB_AIC_Nurse::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ALB_AIC_Nurse::SetState_None()
{
	if (!BB) return;

	BB->SetValueAsEnum("ENurseState", static_cast<uint8>(ENurseState::None));
}

void ALB_AIC_Nurse::SetState_Strafe()
{
	if (!BB) return;

	BB->SetValueAsEnum("ENurseState", static_cast<uint8>(ENurseState::Strafe));
}

void ALB_AIC_Nurse::SetState_SmartObject(int32 Action)
{
	if (!BB) return;

	BB->SetValueAsInt("SOActionNumber", Action);
	BB->SetValueAsEnum("ENurseState", static_cast<uint8>(ENurseState::SmartObject));
}

void ALB_AIC_Nurse::SetState_Interact()
{
	if (!BB) return;

	BB->SetValueAsEnum("ENurseState", static_cast<uint8>(ENurseState::Interact));
}

