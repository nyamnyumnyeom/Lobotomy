// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICMonster_ChainSawMan.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

ALB_AICMonster_ChainSawMan::ALB_AICMonster_ChainSawMan()
{
	PrimaryActorTick.bCanEverTick = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->HearingRange = HearingDistance;
	HearingConfig->SetMaxAge(5.0f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*HearingConfig);
}

void ALB_AICMonster_ChainSawMan::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (bIsRuntimeSpawn)
	{
		SetBB_Target();
	}
	else
	{
		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SetBBTargetTimerHandle, this, &ALB_AICMonsterBase::SetBB_Target, 1.0f, false);
		}
	}
}

void ALB_AICMonster_ChainSawMan::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->ActorHasTag("Player") || Actor->ActorHasTag("SoundActor"))
	{

		if (Stimulus.WasSuccessfullySensed())
		{
			if (Stimulus.Type == UAISense::GetSenseID(UAISense_Hearing::StaticClass()))
			{
				if (CheakPlayerIsIn())
				{
					GetWorld()->GetTimerManager().SetTimer(LostSightTimerHandle, this, &ALB_AICMonsterBase::OnLostSightTimeout, LostSightTime, false);

					if (!BB) return;

					BB->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
					BB->SetValueAsBool("IsSeePlayer", false);

					return;
				}

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
						if (!NavData)
						{
							UE_LOG(LogTemp, Warning, TEXT("NavData not ready"));
							return;
						}

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

		Super::OnPerceptionUpdated(Actor, Stimulus);
	}
}
