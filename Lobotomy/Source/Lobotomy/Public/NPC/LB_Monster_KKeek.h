// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "LB_Monster_KKeek.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_Monster_KKeek : public ALB_MonsterBase
{
	GENERATED_BODY()
	
protected:
	FVector OriginLocation;

protected:
	class ULB_KKeekComp* KKeekComp_Ref;

protected:
	FTimerHandle ResistTimerHandle;

public:
	ALB_Monster_KKeek();

protected:
	virtual void BeginPlay() override;

public:
	// 끽끽이 사라지는 로직.
	// Visibility, Collision, Movement 끄고 원래 위치(배치된 위치)로 이동.
	UFUNCTION(BlueprintCallable)
	void KKeekKKeekInvisible();

	// 끽끽이 등장하는 로직.
	// Visibility, Collision, Movement 켜고 NewLocation으로 이동.
	UFUNCTION(BlueprintCallable)
	void KKeekKKeekVisible(FVector NewLocation);

protected:
	void ResistForPlayer();
};
