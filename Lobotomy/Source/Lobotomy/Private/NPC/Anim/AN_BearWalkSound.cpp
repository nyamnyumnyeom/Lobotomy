// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Anim/AN_BearWalkSound.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

void UAN_BearWalkSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	FVector FootLocation = MeshComp->GetSocketLocation(TEXT("foot_r"));

	if (bIsLeft)
	{
		FootLocation = MeshComp->GetSocketLocation(TEXT("foot_l"));
	}

	USoundBase* WalkSound = nullptr;

	int32 Rand = FMath::RandRange(0, 2);
	switch (Rand)
	{
	case 0:
		WalkSound = WalkSound1;
		break;

	case 1:
		WalkSound = WalkSound2;
		break;

	case 2:
		WalkSound = WalkSound3;
		break;

	default:
		break;
	}

	if (WalkSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			Owner,
			WalkSound,
			FootLocation
		);
	}
}
