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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	class USoundBase* MusicSound;

public:
	float Threshold = 0.95f;

	float MoveDuration = 2.0f;
	float MoveSpeed = 0.3f;

protected:
	ACharacter* PlayerCharacter;

	FVector MoveDirection;
	bool bIsMovingSideways = false;

protected:
	FTimerHandle MoveTimerHandle;

public:
	ALB_MonsterHideAndSeeker();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void StartRandomSideMove();

	void StopRandomSideMove();
};
