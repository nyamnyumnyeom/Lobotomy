// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "TargetPoint_Patient.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ATargetPoint_Patient : public ATargetPoint
{
	GENERATED_BODY()

public:
	// 환자 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> PatientClass;

	// [0:서있기 - Stand] , [1:배회하기 - Strafe], [2:앉아있기 - Sit], [3:누워있기 - Lay], [4:잠자기 - Sleep]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	int32 BehaviorModeChoose = 0;

protected:
	class ALB_PatientBase* SpawnedPatient;

public:
	ATargetPoint_Patient();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float upscale = 0;

protected:
	virtual void BeginPlay() override;

protected:
	void SpawnLogic(TSubclassOf<AActor> SpawnClass);

};
