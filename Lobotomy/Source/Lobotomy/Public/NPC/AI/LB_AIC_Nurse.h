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

protected:
	class ALB_NPC_Nurse* OwnedPawn_Ref;

	float SORotation;

	int32 LastSOAction = -1;

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
	void SetState_SmartObject(int32 Action, FVector SOLocation, float ZRotation);

	UFUNCTION(BlueprintCallable)
	void SetState_Interact();

public:
	UFUNCTION(BlueprintCallable)
	void SOAction_Start();

	// 간호사가 해당 오브젝트에 도달해 SmartObject 로직이 실행되는 경우 어떤 행동을 취하게 할지.
protected:
	// 0 : 허리에 손을 올린 채로 벽을 응시.
	void SOAction_Zero();

	// 1 : 팔짱을 낀 채로 책상 등을 응시.
	void SOAction_One();

	// 2 : 문을 두드린 후 열어봄.
	void SOAction_Two();

	// 3 : 환자와 대화를 시도함.
	void SOAction_Three();

};
