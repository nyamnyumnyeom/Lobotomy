// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LB_Interface_MonsterState.generated.h"

/**
 *
 */
UINTERFACE(Blueprintable)
class UCheakingState : public UInterface
{
	GENERATED_BODY()
};

class ICheakingState : public IInterface
{
	GENERATED_BODY()

public:
	// Behavior Tree에서 호출될 인터페이스 함수. 
	// 해당 캐릭터가 사라져야 하는지 확인하는 용도.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	bool CheakShouldDestroy();

	// Behavior Tree에서 호출될 인터페이스 함수. 
	// 해당 캐릭터가 Chase 상태인지 확인하는 용도.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void CheckIsChase(bool bIsChase);

	// 문 근처를 지나가며 문을 열때 호출될 함수.
	// 잠시 이동을 멈추는 용도.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void StopMovemontAtDoor();
};

