// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AIC_Nurse.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/LB_NPC_Nurse.h"


ALB_AIC_Nurse::ALB_AIC_Nurse()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALB_AIC_Nurse::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnedPawn_Ref = Cast<ALB_NPC_Nurse>(GetPawn());
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

void ALB_AIC_Nurse::SetState_SmartObject(int32 Action, FVector SOLocation, float ZRotation)
{
	if (!BB) return;

	LastSOAction = Action;
	SORotation = ZRotation;
	BB->SetValueAsInt("SOActionNumber", Action);
	BB->SetValueAsVector("NextLocation", SOLocation);
	BB->SetValueAsEnum("ENurseState", static_cast<uint8>(ENurseState::SmartObject));
}

void ALB_AIC_Nurse::SetState_Interact()
{
	if (!BB) return;

	BB->SetValueAsEnum("ENurseState", static_cast<uint8>(ENurseState::Interact));
}

void ALB_AIC_Nurse::SOAction_Start()
{
	if (OwnedPawn_Ref)
	{
		FRotator NewRotation = OwnedPawn_Ref->GetActorRotation();
		NewRotation.Yaw = SORotation;
		OwnedPawn_Ref->SetActorRotation(NewRotation);
	}
	else
	{
		OwnedPawn_Ref = Cast<ALB_NPC_Nurse>(GetPawn());
	}

	switch (LastSOAction)
	{
	case 0:
		SOAction_Zero();
		break;

	case 1:
		SOAction_One();
		break;

	case 2:
		SOAction_Two();
		break;

	case 3:
		SOAction_Three();
		break;

	default:
		break;
	}
}

void ALB_AIC_Nurse::SOAction_Zero()
{
	if (OwnedPawn_Ref)
	{
		OwnedPawn_Ref->PlayAnimation_Zero();
	}
	else
	{
		OwnedPawn_Ref = Cast<ALB_NPC_Nurse>(GetPawn());
	}
}

void ALB_AIC_Nurse::SOAction_One()
{
	if (OwnedPawn_Ref)
	{
		OwnedPawn_Ref->PlayAnimation_One();
	}
	else
	{
		OwnedPawn_Ref = Cast<ALB_NPC_Nurse>(GetPawn());
	}
}

void ALB_AIC_Nurse::SOAction_Two()
{
	if (OwnedPawn_Ref)
	{
		OwnedPawn_Ref->PlayAnimation_Two();
	}
	else
	{
		OwnedPawn_Ref = Cast<ALB_NPC_Nurse>(GetPawn());
	}
}

void ALB_AIC_Nurse::SOAction_Three()
{
	if (OwnedPawn_Ref)
	{
		OwnedPawn_Ref->PlayAnimation_Three();
	}
	else
	{
		OwnedPawn_Ref = Cast<ALB_NPC_Nurse>(GetPawn());
	}
}

