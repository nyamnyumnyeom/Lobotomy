// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICMonsterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NPC/LB_NPCData.h"
#include "NavigationSystem.h"

ALB_AICMonsterBase::ALB_AICMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = SightDistance;
	SightConfig->LoseSightRadius = SightDistance + 200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 50.0f;
	SightConfig->SetMaxAge(LostSightTime);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->HearingRange = HearingDistance;
	HearingConfig->SetMaxAge(5.0f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->ConfigureSense(*HearingConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ALB_AICMonsterBase::OnPerceptionUpdated);
}

void ALB_AICMonsterBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BB)
	{
		APawn* TargetActor = UGameplayStatics::GetPlayerPawn(this, 0);
		if (TargetActor)
		{
			BB->SetValueAsObject("Target", TargetActor);
			SetFocus(TargetActor);
		}
	}
}

void ALB_AICMonsterBase::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor->ActorHasTag("Player")) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass()))
		{
			GetWorld()->GetTimerManager().ClearTimer(LostSightTimerHandle);

			SetState_Investigation_Sight();
		}

		if (Stimulus.Type == UAISense::GetSenseID(UAISense_Hearing::StaticClass()))
		{
			FVector SoundLocation = Stimulus.StimulusLocation;
			FVector MyLocation = GetPawn()->GetActorLocation();

			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(GetPawn());

			bool bBlocked = GetWorld()->LineTraceSingleByChannel(
				Hit,
				MyLocation,
				SoundLocation,
				ECC_Visibility,
				Params
			);

			if (!bBlocked)
			{
				SetState_Investigation_Hear(SoundLocation);
			}
			else
			{
				UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
				if (NavSys)
				{

					FNavAgentProperties AgentProps = this->GetNavAgentPropertiesRef();
					ANavigationData* NavData = NavSys->GetNavDataForProps(AgentProps);

					FVector StartLocation = MyLocation;
					FVector EndLocation = SoundLocation;

					FPathFindingQuery Query(this, *NavData, StartLocation, EndLocation);
					FPathFindingResult Result = NavSys->FindPathSync(Query);

					if (Result.Path.IsValid() && Result.Result == ENavigationQueryResult::Success)
					{
						const float PathDistance = Result.Path->GetLength();

						if (PathDistance <= HearingDistance)
						{
							SetState_Investigation_Hear(SoundLocation);
						}
					}
				}
			}
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

void ALB_AICMonsterBase::SetState_Idle()
{
	if (!BB) return;

	BB->SetValueAsEnum("CurrentState", static_cast<uint8>(EMonsterState::Idle));
}

void ALB_AICMonsterBase::SetState_Investigation_Hear(FVector Location)
{
	if (!BB) return;

	if (static_cast<EMonsterState>(BB->GetValueAsEnum("CurrentState")) == EMonsterState::Idle)
	{
		BB->SetValueAsEnum("CurrentState", static_cast<uint8>(EMonsterState::Investigation));
	}

	BB->SetValueAsVector("LastSeenLocation", Location);
}

void ALB_AICMonsterBase::SetState_Investigation_Sight()
{
	if (!BB) return;

	if (static_cast<EMonsterState>(BB->GetValueAsEnum("CurrentState")) == EMonsterState::Idle)
	{
		BB->SetValueAsEnum("CurrentState", static_cast<uint8>(EMonsterState::Investigation));
	}

	BB->SetValueAsBool("IsSeePlayer", true);
}

void ALB_AICMonsterBase::SetState_Chase()
{
	if (!BB) return;

	BB->SetValueAsEnum("CurrentState", static_cast<uint8>(EMonsterState::Chase));
}

void ALB_AICMonsterBase::OnLostSightTimeout()
{
	if (!BB) return;

	BB->SetValueAsEnum("CurrentState", static_cast<uint8>(EMonsterState::Investigation));

	GetWorld()->GetTimerManager().SetTimer(LostSightTimerHandle, this, &ALB_AICMonsterBase::SetState_Idle, SetIdleTime, false);
}

void ALB_AICMonsterBase::SetPerceptionSwitch(bool Value)
{
	if (Value)
	{
		if (AIPerception)
		{
			AIPerception->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
			AIPerception->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
		}
	}
	else
	{
		if (AIPerception)
		{
			AIPerception->SetSenseEnabled(UAISense_Sight::StaticClass(), false);
			AIPerception->SetSenseEnabled(UAISense_Hearing::StaticClass(), false);
		}
	}
}

void ALB_AICMonsterBase::StopBehaviorTree()
{
	UBehaviorTreeComponent* BTC = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTC)
	{
		BTC->StopTree(EBTStopMode::Forced);
	}
}
