// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LB_SaveSetting.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ULB_SaveSetting : public USaveGame
{
	GENERATED_BODY()

	// Volume
public:
	UPROPERTY()
	int32 Volume_Master = 50;

public:
	ULB_SaveSetting();
};
