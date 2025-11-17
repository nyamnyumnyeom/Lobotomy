// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "LB_MonsterHideAndSeeker.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_MonsterHideAndSeeker : public ALB_MonsterBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* PlayerDetectSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> KnockSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> LaghingSounds;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "See")
	float Threshold = 0.95f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveDuration = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveSpeed = 0.3f;

protected:
	ACharacter* PlayerCharacter;

	FVector MoveDirection;
	bool bIsMovingSideways = false;
	bool bShouldLogicStop = false;

protected:
	FTimerHandle MoveTimerHandle;
	FTimerHandle BeginPlayTimerHandle;
	FTimerHandle DestroyTimerHandle;

public:
	ALB_MonsterHideAndSeeker();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void StartRandomSideMove();

	void StopRandomSideMove();

	void RealDestroy();
};
