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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Detection")
	bool CheakShouldDestroy();
};

