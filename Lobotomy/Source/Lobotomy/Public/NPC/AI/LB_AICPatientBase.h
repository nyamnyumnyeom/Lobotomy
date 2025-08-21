// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICBase.h"
#include "NPC/LB_NPCData.h"
#include "LB_AICPatientBase.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICPatientBase : public ALB_AICBase
{
	GENERATED_BODY()

public:
	// 환자의 행동 상태 초기화. [None : 안움직임], [Strafe : 주변 배회], [Action : 임의 행동]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPatientState PatientState;

public:
	ALB_AICPatientBase();

public:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetState_None();

	UFUNCTION(BlueprintCallable)
	void SetState_Strafe();

	UFUNCTION(BlueprintCallable)
	void SetState_Action();
};
