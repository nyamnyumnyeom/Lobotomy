// Fill out your copyright notice in the Description page of Project Settings.


#include "SurpriseActor/LB_SurpriseBed.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ALB_SurpriseBed::ALB_SurpriseBed()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALB_SurpriseBed::SurprisEventStart()
{
	if (!bCanSurprise) return;

	bCanSurprise = false;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &ALB_SurpriseBed::Surprise_Reset, ResetTime, false);
	}

	PlaySound_Surprise();

	PlayAnimation_Surprise();
}

void ALB_SurpriseBed::PlaySound_Surprise()
{
	if (!SurpriseSound) return;

	UGameplayStatics::PlaySoundAtLocation(this, SurpriseSound, GetActorLocation());
}

void ALB_SurpriseBed::PlayAnimation_Surprise()
{
	if (SurpriseMontage && SkeletalMeshComp)
	{
		UAnimInstance* AnimInstance = SkeletalMeshComp->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(SurpriseMontage);
		}
	}
}

void ALB_SurpriseBed::Surprise_Reset()
{
	bCanSurprise = true;
}
