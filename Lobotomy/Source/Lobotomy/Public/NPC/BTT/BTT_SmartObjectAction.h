// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SmartObjectAction.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_SmartObjectAction : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_SmartObjectAction();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
