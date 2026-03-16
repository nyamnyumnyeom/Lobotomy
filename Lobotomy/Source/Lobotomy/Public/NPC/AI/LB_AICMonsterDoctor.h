// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICMonsterBase.h"
#include "LB_AICMonsterDoctor.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICMonsterDoctor : public ALB_AICMonsterBase
{
	GENERATED_BODY()

public:
	ALB_AICMonsterDoctor();

	virtual void OnPossess(APawn* InPawn) override;
};
