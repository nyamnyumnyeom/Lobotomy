// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICMonsterBase.h"
#include "LB_AICMonster_ChainSawMan.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICMonster_ChainSawMan : public ALB_AICMonsterBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	class UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HearingDistance = 1200.0f;

public:
	ALB_AICMonster_ChainSawMan();

	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;

};
