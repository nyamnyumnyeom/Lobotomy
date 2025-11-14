// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LB_AICBase.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICBase : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBlackboardComponent* BB;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BT;

public:
	ALB_AICBase();

public:
	virtual void OnPossess(APawn* InPawn) override;
};
