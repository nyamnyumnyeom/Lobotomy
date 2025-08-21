// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICPatientBase.h"
#include "BehaviorTree/BlackboardComponent.h"

ALB_AICPatientBase::ALB_AICPatientBase()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ALB_AICPatientBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	switch (PatientState)
	{
	case EPatientState::None:
		SetState_None();
		break;

	case EPatientState::Strafe:
		SetState_Strafe();
		break;

	case EPatientState::Action:
		SetState_Action();
		break;

	default:
		break;
	}
}

void ALB_AICPatientBase::SetState_None()
{
	if (!BB) return;

	BB->SetValueAsEnum("EPatientState", static_cast<uint8>(EPatientState::None));
}

void ALB_AICPatientBase::SetState_Strafe()
{
	if (!BB) return;

	BB->SetValueAsEnum("EPatientState", static_cast<uint8>(EPatientState::Strafe));
}

void ALB_AICPatientBase::SetState_Action()
{
	if (!BB) return;

	BB->SetValueAsEnum("EPatientState", static_cast<uint8>(EPatientState::Action));
}
