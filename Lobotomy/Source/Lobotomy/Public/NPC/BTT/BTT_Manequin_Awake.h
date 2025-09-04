// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Manequin_Awake.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_Manequin_Awake : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_Manequin_Awake();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
