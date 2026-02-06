// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_BearWalk.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API UANS_BearWalk : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Move")
	float TotalDistance = 30.0f;

private:
	float MovedDistance = 0.0f;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

};
