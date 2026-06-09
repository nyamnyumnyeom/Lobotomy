// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_NPCBase.h"
#include "NPC/Interface/LB_Interface_MonsterState.h"
#include "LB_MonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_MonsterBase : public ALB_NPCBase, public ICheakingState
{
	GENERATED_BODY()
	
public:
	ALB_MonsterBase();

public:
	// Behavior Tree에서 호출될 인터페이스 함수. 해당 캐릭터가 사라져야 하는지 확인하는 용도이며, 각 클래스에서 재정의 필수.
	virtual bool CheakShouldDestroy_Implementation() override;

	// Behavior Tree에서 호출될 인터페이스 함수. 각 클래스에서 재정의 필수.
	// 해당 캐릭터가 Chase 상태인지 확인하는 용도.
	virtual void CheckIsChase_Implementation(bool bIsChase) override;

	// 문 근처를 지나가며 문을 열때 호출될 함수.
	// 잠시 이동을 멈추는 용도.
	virtual void StopMovemontAtDoor_Implementation() override;

public:
	virtual void DisappearLogic();

	UFUNCTION(BlueprintCallable, Category = "Sanity")
	void Sanity_Reduces(float Amount, AActor* SanityActor);

	bool CheakPlayerIsIn();

};
