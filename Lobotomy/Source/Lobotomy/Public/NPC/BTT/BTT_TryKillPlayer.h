// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_TryKillPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_TryKillPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// 사망 종류
	// 0 : 전기톱
	// 1 : 노커
	// 2 : 끾끾끾
	// 3: 곰탬미
	// 10 : 낮에 시간초과
	// 11 : 밤에 시간초과
	UPROPERTY(EditAnywhere, Category = "Death")
	int32 DeathNumber = 0;

	UPROPERTY(EditAnywhere, Category = "Death")
	bool bIsChainSaw = true;

public:
	UBTT_TryKillPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
