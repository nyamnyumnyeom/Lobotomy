// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Sound/SoundBase.h"
#include "LB_FootSteps_Paitent.generated.h"

UCLASS()
class LOBOTOMY_API ULB_FootSteps_Paitent : public UAnimNotify
{
	GENERATED_BODY()
public:

	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation
	) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	USoundBase* FootstepSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	float VolumeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	float PitchMin = 0.95f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
	float PitchMax = 1.05f;
};