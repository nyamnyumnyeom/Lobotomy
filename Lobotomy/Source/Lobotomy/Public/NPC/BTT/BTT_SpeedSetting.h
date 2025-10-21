// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SpeedSetting.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_SpeedSetting : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_SpeedSetting();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
