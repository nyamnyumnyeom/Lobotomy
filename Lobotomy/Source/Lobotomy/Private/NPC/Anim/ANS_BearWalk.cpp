// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Anim/ANS_BearWalk.h"

void UANS_BearWalk::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	float Step = (TotalDistance / Animation->GetPlayLength()) * FrameDeltaTime;
	FVector Forward = Owner->GetActorForwardVector();

	Owner->AddActorWorldOffset(Forward * Step, true);
}
