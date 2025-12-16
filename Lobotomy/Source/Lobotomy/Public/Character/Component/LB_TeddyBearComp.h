// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LB_TeddyBearComp.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API ULB_TeddyBearComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// 플레이어 캐릭터 기준 타겟 포인트를 검사할 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SphereTraceRadius = 1000.0f;

	// 몇초에 한번씩 로직을 작동시킬지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float TriggerLoopTime = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float Threshold = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	bool bIsChecked = false;

protected:
	class ALB_GM* GM;

protected:
	FTimerHandle TriggerLoopTimerHandle;

public:	
	ULB_TeddyBearComp();

protected:
	virtual void BeginPlay() override;

public:	
	// 곰인형 조건 검사 타이머 시작.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerTeddyBearActive();

	// 곰인형을 작동시킬 조건이 충족되는지 검사.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerTeddyBearLoop();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerLoopTimerClear();

};
