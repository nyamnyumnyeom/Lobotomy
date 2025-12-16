// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICBase.h"
#include "NPC/LB_NPCData.h"
#include "LB_AIC_Nurse.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AIC_Nurse : public ALB_AICBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	ENurseState NurseState;

public:
	ALB_AIC_Nurse();

public:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetState_None();

	UFUNCTION(BlueprintCallable)
	void SetState_Strafe();

	UFUNCTION(BlueprintCallable)
	void SetState_SmartObject(int32 Action);

	UFUNCTION(BlueprintCallable)
	void SetState_Interact();
};
