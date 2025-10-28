// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_NPCBase.h"
#include "LB_PatientBase.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_PatientBase : public ALB_NPCBase
{
	GENERATED_BODY()

public:
	// 순서대로 저장 필수 [0 : 서있기-Stand], [1 : 배회하기-Strafe], [2 : 앉아있기-Sit], [3 : 누워있기-Lay], [4 : 잠자기-Sleep]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<TSubclassOf<UAnimInstance>> AnimBlueprintPresets;

	// [0:서있기 - Stand] , [1:배회하기 - Strafe], [2:앉아있기 - Sit], [3:누워있기 - Lay], [4:잠자기 - Sleep]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	int32 BehaviorMode = 0;

public:
	ALB_PatientBase();

public:
	// [0:서있기 - Stand] , [1:배회하기 - Strafe], [2:앉아있기 - Sit], [3:누워있기 - Lay], [4:잠자기 - Sleep]
	UFUNCTION(BlueprintCallable)
	void ApplyAnimBlueprint(int32 Index);
};
