// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NPC/LB_NPCData.h"
#include "BTT_ChangeNurseState.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UBTT_ChangeNurseState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	ENurseState NewState;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector AIStateKey;

public:
	UBTT_ChangeNurseState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
