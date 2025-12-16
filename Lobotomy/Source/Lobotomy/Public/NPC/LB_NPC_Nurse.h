// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_NPCBase.h"
#include "LB_NPC_Nurse.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_NPC_Nurse : public ALB_NPCBase
{
	GENERATED_BODY()

public:
	// 간호사 기준 Smart Object를 검사할 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SphereTraceRadius = 500.0f;

	// Smart Object를 검사할 시간(반복)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SO_CheckTime = 3.0f;

protected:
	FTimerHandle SOCheackTimerHandle;
	FTimerHandle OwnerAICResistTimerHandle;

protected:
	int32 LastSOAction = -1;

protected:
	class ALB_AIC_Nurse* OwnerAICReference;

public:
	ALB_NPC_Nurse();

protected:
	virtual void BeginPlay() override;

public:
	// 간호사가 해당 오브젝트에 도달해 SmartObject 로직이 실행되는 경우 어떤 행동을 취하게 할지.
	// 0 : 허리에 손을 올린 채로 벽을 응시.
	// 1 : 팔짱을 낀 채로 책상 등을 응시.
	// 2 : 문을 두드린 후 열어봄.
	// 3 : 환자와 대화를 시도함.
	UFUNCTION(BlueprintCallable)
	void SOAction();

	void Check_SO();

public:
	UFUNCTION(BlueprintCallable)
	void TimerOn_InteractSO();

	UFUNCTION(BlueprintCallable)
	void TimerOff_InteractSO();

protected:
	void Resist_OwnerAIC();
};
