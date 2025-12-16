// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/AI/LB_AICMonsterBase.h"
#include "LB_AICMonster_Manequin.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_AICMonster_Manequin : public ALB_AICMonsterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Perception")
	class UAISenseConfig_Hearing* HearingConfig;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HearingDistance = 600.0f;

	float SightDistance = 1500.0f;

protected:
	// Reference
	class ALB_Monster_Manequin* OwnedPawnReference;

	ACharacter* PlayerCharacterReference;
	AActor* PlayerCharacterReference_AActor;

	bool bIsGMResist = false;

public:
	ALB_AICMonster_Manequin();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Manequin")
	void MoveToPlayerBackward(bool bShouldMove = false);

protected:
	void Resist_OwnedPawn();
	void Resist_PlayerCharacter();

	void Resist_ToGM();
};
