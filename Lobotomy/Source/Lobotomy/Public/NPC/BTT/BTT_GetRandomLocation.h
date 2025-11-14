// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_GetRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// 생성할 랜덤 위치의 최대 반경
	UPROPERTY(EditAnywhere, Category = "Location")
	float LocationRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Location")
	struct FBlackboardKeySelector LocationKey;

public:
	UBTT_GetRandomLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
