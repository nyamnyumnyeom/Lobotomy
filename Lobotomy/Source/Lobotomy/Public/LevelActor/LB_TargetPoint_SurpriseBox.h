// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "LB_TargetPoint_SurpriseBox.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_TargetPoint_SurpriseBox : public ATargetPoint
{
	GENERATED_BODY()

public:
	// 깜짝 상자 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> SurpriseBoxClass;

public:
	// 깜짝 상자일 백분율. 
	// 60일 경우 열었을 때 60% 확률로 깜짝 인형이 등장하거나 40% 확률로 배터리 등장.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int32 SurpriseProbability = 50;

protected:
	UPROPERTY()
	class ALB_SurpriseBox* SpawnedSurpriseBox;

public:
	ALB_TargetPoint_SurpriseBox();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnSurpriseBox();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DespawnSurpriseBox();
};
