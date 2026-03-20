// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "LBTargetPoint_Doctor.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALBTargetPoint_Doctor : public ATargetPoint
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* SphereCollision;

public:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> DoctorClass;

protected:
	AActor* SpawnedDoctorClass;

public:
	ALBTargetPoint_Doctor();

protected:
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintCallable)
	void SpawnDoctorClass();

	UFUNCTION(BlueprintCallable)
	void DisableCollision();
	
};
