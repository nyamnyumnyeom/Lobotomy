// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICMonster_TeddyBear.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ALB_AICMonster_TeddyBear::ALB_AICMonster_TeddyBear()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALB_AICMonster_TeddyBear::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetBB_Target();
}

void ALB_AICMonster_TeddyBear::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor->ActorHasTag("Player")) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass()))
		{
			if (CheakPlayerIsIn())
			{
				GetWorld()->GetTimerManager().SetTimer(LostSightTimerHandle, this, &ALB_AICMonsterBase::OnLostSightTimeout, LostSightTime, false);

				if (!BB) return;

				BB->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
				BB->SetValueAsBool("IsSeePlayer", false);
			}

			GetWorld()->GetTimerManager().ClearTimer(LostSightTimerHandle);

			SetBB_Target();
			SetState_Chase();
		}
	}
	else
	{
		if (Stimulus.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass()))
		{
			GetWorld()->GetTimerManager().SetTimer(LostSightTimerHandle, this, &ALB_AICMonsterBase::OnLostSightTimeout, LostSightTime, false);

			if (!BB) return;

			BB->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
			BB->SetValueAsBool("IsSeePlayer", false);
		}
	}
}
