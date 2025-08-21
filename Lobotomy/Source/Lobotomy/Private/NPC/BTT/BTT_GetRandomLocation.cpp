// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_GetRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_GetRandomLocation::UBTT_GetRandomLocation()
{
	NodeName = TEXT("Get Random Location");

	LocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetRandomLocation, LocationKey));
}

EBTNodeResult::Type UBTT_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	UWorld* World = ControlledPawn->GetWorld();
	if (!World) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (!NavSys) return EBTNodeResult::Failed;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	FNavLocation RandomLocation;
	bool bFound = NavSys->GetRandomReachablePointInRadius(
		ControlledPawn->GetActorLocation(),
		LocationRadius,
		RandomLocation
	);

	if (bFound)
	{
		 BB->SetValueAsVector(LocationKey.SelectedKeyName, RandomLocation.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
