// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICPatientBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/LB_PatientBase.h"

ALB_AICPatientBase::ALB_AICPatientBase()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ALB_AICPatientBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	NPC = Cast<ALB_PatientBase>(InPawn);

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(SettingTimerHandle, this, &ALB_AICPatientBase::SetBehaviorAndAnim, 0.5f, false);
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

void ALB_AICPatientBase::SetBehaviorAndAnim()
{
	if (!NPC) return;

	switch (NPC->BehaviorMode)
	{
	case 0:
		SetState_None();
		NPC->ApplyAnimBlueprint(0);
		break;

	case 1:
		SetState_Strafe();
		NPC->ApplyAnimBlueprint(1);
		break;

	case 2:
		SetState_None();
		NPC->ApplyAnimBlueprint(2);
		break;

	case 3:
		SetState_None();
		NPC->ApplyAnimBlueprint(3);
		break;

	case 4:
		SetState_None();
		NPC->ApplyAnimBlueprint(4);
		break;

	default:
		break;
	}
}
