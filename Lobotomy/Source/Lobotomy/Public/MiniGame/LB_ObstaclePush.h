// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_ObstaclePush.generated.h"

UCLASS()
class LOBOTOMY_API ALB_ObstaclePush : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	float LocationU = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	float LocationV = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float MaxOffset = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 TimeUpTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 TimeRequired = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float TimerDelay = 0.016f;

protected:
	float HoveredTime = 0.0f;

	float MaxLocationU = 300.0f;
	float MaxLocationV = 300.0f;

	float StartValue_U;
	float TargetValue_U;
	float ChangeDuration_U;
	float ElapsedTime_U;

	float StartValue_V;
	float TargetValue_V;
	float ChangeDuration_V;
	float ElapsedTime_V;

protected:
	FTimerHandle MiniGameTimerHandle;
	FTimerHandle HoverTimerHandle;

	FTimerHandle LocationUTimerHandle;
	FTimerHandle LocationVTimerHandle;

public:	
	ALB_ObstaclePush();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartMiniGameTimer();

	UFUNCTION(BlueprintCallable)
	void EndMiniGameTimer(bool& Result);

	UFUNCTION(BlueprintCallable)
	void HoveredTimeResume();

	UFUNCTION(BlueprintCallable)
	void HoveredTimePause();

	void UpdateHoveredTime();

	UFUNCTION(BlueprintImplementableEvent)
	void TimeOver();

public:	
	UFUNCTION(BlueprintCallable)
	void StartChange_U(float MaxU);

	UFUNCTION(BlueprintCallable)
	void StartChange_V(float MaxV);

	UFUNCTION(BlueprintCallable)
	void StopMovingTimer();

	void UpdateLocationU();

	void UpdateLocationV();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateLocation();
};
