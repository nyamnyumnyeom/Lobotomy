// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LB_Interface_SmartObject.generated.h"

/**
 *
 */
UINTERFACE(Blueprintable)
class USO_Nurse : public UInterface
{
	GENERATED_BODY()
};

class ISO_Nurse : public IInterface
{
	GENERATED_BODY()

public:
	// Smart Object에서 호출될 인터페이스 함수. 
	// 간호사에게 어떤 행동을 해야할지 알려주는 용도.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Smart Object")
	int32 CheakNurseSOAction();

};
