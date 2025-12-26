// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_DrawerSlot.generated.h"

UCLASS()
class LOBOTOMY_API ALB_DrawerSlot : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Components")
	class UStaticMeshComponent* DrawerMeshComponent;

	// 깜짝 상자 스폰 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UBillboardComponent* SpawnBillboard;

public:
	// 깜짝 상자 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> SurpriseBoxClass;

public:
	// 밤이 되었을 때 깜짝 상자가 스폰될 확률.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int32 SpawnProbability = 50;

	// 깜짝 상자일 백분율. 
	// 60일 경우 열었을 때 60% 확률로 깜짝 인형이 등장하거나 40% 확률로 배터리 등장.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int32 SurpriseProbability = 50;

	// 현재 깜짝 상자가 스폰되어 있느가?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	bool bIsBoxSpawned = false;

	// 현재 깜짝 상자가 스폰되어 있느가?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	bool bIsSurpriseDelay = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	class ALB_SurpriseBox* SpawnedSurpriseBox;

public:	
	// Sets default values for this actor's properties
	ALB_DrawerSlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnSurpriseBox();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DespawnSurpriseBox();

};
