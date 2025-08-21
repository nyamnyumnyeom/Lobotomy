// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICBase.h"
#include "LB_AICMonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICMonsterBase : public ALB_AICBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	class UAIPerceptionComponent* AIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	class UAISenseConfig_Hearing* HearingConfig;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SightDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HearingDistance = 1200.0f;

	// Perception의 Sight를 벗어난 뒤 해당 초만큼 지나면 플레이어 감지를 잃고, Investigation 상태로 변경 후 마지막 감지 위치로 이동.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float LostSightTime = 5.0f;

	// Investigation 상태에서 해당 초 내에 플레이어가 감지되지 않으면 Idle 상태로 변경.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SetIdleTime = 5.0f;

	// Blackboard의 Target값 할당 딜레이 적용여부. True일 경우 즉시 할당.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bIsRuntimeSpawn = false;

protected:
	FTimerHandle SetBBTargetTimerHandle;

	FTimerHandle LostSightTimerHandle;
	FTimerHandle ChaseTimerHandle;
	FTimerHandle PerceptionTimerHandle;

public:
	ALB_AICMonsterBase();

	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:
	UFUNCTION(BlueprintCallable)
	void SetState_Idle();

	UFUNCTION(BlueprintCallable)
	void SetState_Investigation_Hear(FVector Location);

	UFUNCTION(BlueprintCallable)
	void SetState_Investigation_Sight();

	UFUNCTION(BlueprintCallable)
	void SetState_Chase();

public:
	UFUNCTION(BlueprintCallable)
	void OnLostSightTimeout();

public:
	UFUNCTION(BlueprintCallable)
	void SetPerceptionSwitch(bool Value);

	UFUNCTION(BlueprintCallable)
	void StopBehaviorTree();

protected:
	void SetBB_Target();
};
