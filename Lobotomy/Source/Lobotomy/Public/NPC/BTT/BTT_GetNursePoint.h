// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetNursePoint.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_GetNursePoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Location")
	struct FBlackboardKeySelector LocationKey;

public:
	UBTT_GetNursePoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
