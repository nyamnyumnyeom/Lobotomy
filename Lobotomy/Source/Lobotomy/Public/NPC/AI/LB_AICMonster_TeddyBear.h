// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICMonsterBase.h"
#include "LB_AICMonster_TeddyBear.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICMonster_TeddyBear : public ALB_AICMonsterBase
{
	GENERATED_BODY()
	
public:
	ALB_AICMonster_TeddyBear();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
};
