// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/AI/LB_AICMonster_Manequin.h"
#include "NPC/LB_Monster_Manequin.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h" 
#include "Perception/AISenseConfig_Hearing.h"
#include "NavigationSystem.h"
#include "LB_GM.h"

ALB_AICMonster_Manequin::ALB_AICMonster_Manequin()
{
	PrimaryActorTick.bCanEverTick = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->HearingRange = HearingDistance;
	HearingConfig->SetMaxAge(5.0f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
}

void ALB_AICMonster_Manequin::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(SetBBTargetTimerHandle, this, &ALB_AICMonster_Manequin::Resist_OwnedPawn, 1.0f, false);
		GetWorldTimerManager().SetTimer(SetBBTargetTimerHandle, this, &ALB_AICMonster_Manequin::Resist_PlayerCharacter, 1.0f, false);
	}
}

void ALB_AICMonster_Manequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALB_AICMonster_Manequin::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnPerceptionUpdated(Actor, Stimulus);

	if (!Actor->ActorHasTag("Player")) return;

	if (Stimulus.Type == UAISense::GetSenseID(UAISense_Hearing::StaticClass()))
	{
		Resist_ToGM();

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
			SetState_Chase();
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
						SetState_Chase();
					}
				}
			}
		}
	}
}

void ALB_AICMonster_Manequin::MoveToPlayerBackward(bool bShouldMove)
{
	if (!PlayerCharacterReference_AActor) return;

	if (bShouldMove)
	{
		SetFocus(PlayerCharacterReference_AActor);
		MoveToActor(PlayerCharacterReference_AActor, 150.0f, true, true, true, 0, true);

		FVector PlayerLocation = PlayerCharacterReference_AActor->GetActorLocation();
		FString DebugMsg = FString::Printf(TEXT("Player Location : %f, %f"), PlayerLocation.X, PlayerLocation.Y);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, DebugMsg);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Where are you eyes on?"));
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Player look at me!"));
	}
}

void ALB_AICMonster_Manequin::Resist_OwnedPawn()
{
	OwnedPawnReference = Cast<ALB_Monster_Manequin>(GetPawn());

	if (OwnedPawnReference) return;
	
	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(SetBBTargetTimerHandle, this, &ALB_AICMonster_Manequin::Resist_OwnedPawn, 1.0f, false);
	}
	
}

void ALB_AICMonster_Manequin::Resist_PlayerCharacter()
{
	PlayerCharacterReference = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacterReference)
	{
		PlayerCharacterReference_AActor = Cast<AActor>(PlayerCharacterReference);
		if (PlayerCharacterReference_AActor)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("Player_Actor Resist success!"));
		}
	}
	else
	{
		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SetBBTargetTimerHandle, this, &ALB_AICMonster_Manequin::Resist_PlayerCharacter, 1.0f, false);
		}
	}
}

void ALB_AICMonster_Manequin::Resist_ToGM()
{
	if (bIsGMResist) return;

	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;

	bIsGMResist = true;

	GM->ManequinSpawnDay = true;
}
