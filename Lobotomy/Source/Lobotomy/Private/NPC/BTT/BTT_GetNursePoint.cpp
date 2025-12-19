// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_GetNursePoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/LB_TargetPoint_Nurse.h"
#include "Kismet/GameplayStatics.h"

UBTT_GetNursePoint::UBTT_GetNursePoint()
{
	NodeName = TEXT("Get Random Nurse Point Location");

	LocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetNursePoint, LocationKey));
}

EBTNodeResult::Type UBTT_GetNursePoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	UWorld* World = ControlledPawn->GetWorld();
	if (!World) return EBTNodeResult::Failed;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	TArray<AActor*> FoundPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALB_TargetPoint_Nurse::StaticClass(), FoundPoints);

	if (FoundPoints.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, FoundPoints.Num() - 1);

		AActor* TargetActor = FoundPoints[RandomIndex];
		if (TargetActor)
		{
			BB->SetValueAsVector(LocationKey.SelectedKeyName, TargetActor->GetActorLocation());

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
