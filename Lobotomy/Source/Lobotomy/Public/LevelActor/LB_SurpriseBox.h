// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_SurpriseBox.generated.h"

UCLASS()
class LOBOTOMY_API ALB_SurpriseBox : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> BatteryClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSurprise = true;

public:	
	// Sets default values for this actor's properties
	ALB_SurpriseBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnBattery();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DespawnBattery();

};
