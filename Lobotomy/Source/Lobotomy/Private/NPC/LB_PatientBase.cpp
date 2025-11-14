// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_PatientBase.h"

ALB_PatientBase::ALB_PatientBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Patient"));
}

void ALB_PatientBase::ApplyAnimBlueprint(int32 Index)
{
	if (AnimBlueprintPresets.Num() == 0) return;

	TSubclassOf<UAnimInstance> SelectedAnimBP = AnimBlueprintPresets[Index];

	USkeletalMeshComponent* SkelMesh = GetMesh();
	if (SkelMesh && SelectedAnimBP)
	{
		SkelMesh->SetAnimInstanceClass(SelectedAnimBP);
	}
}
