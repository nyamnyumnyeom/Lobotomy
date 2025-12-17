// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_NPC_Nurse.h"
#include "NPC/Interface/LB_Interface_SmartObject.h"
#include "NPC/AI/LB_AIC_Nurse.h"

ALB_NPC_Nurse::ALB_NPC_Nurse()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALB_NPC_Nurse::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(OwnerAICResistTimerHandle, this, &ALB_NPC_Nurse::Resist_OwnerAIC, 1.0f, false);
	}
}

void ALB_NPC_Nurse::Check_SO()
{
	UWorld* World = GetWorld();
	if (!World) return;

	FVector Start = GetActorLocation();
	float Radius = SphereTraceRadius;

	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	bool bHit = World->SweepMultiByChannel(
		HitResults,
		Start,
		Start,
		FQuat::Identity,
		ECC_WorldDynamic,
		Sphere
	);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->Implements<USO_Nurse>())
			{
				LastSOAction = ISO_Nurse::Execute_CheakNurseSOAction(HitActor);

				SOAction(HitActor->GetActorLocation(), HitActor->GetActorRotation().Yaw);
			}
		}
	}
}

void ALB_NPC_Nurse::PlayAnimation_Zero()
{
	if (!Montage_Zero) return;

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (!AnimInst) return;

	float PlayTime = AnimInst->Montage_Play(Montage_Zero);
	if (PlayTime <= 0.f) return;

	TimerOff_InteractSO();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ALB_NPC_Nurse::OnSOZeroMontageEnded);
	AnimInst->Montage_SetEndDelegate(EndDelegate, Montage_Zero);
}

void ALB_NPC_Nurse::PlayAnimation_One()
{
	if (!Montage_One) return;

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (!AnimInst) return;

	float PlayTime = AnimInst->Montage_Play(Montage_One);
	if (PlayTime <= 0.f) return;

	TimerOff_InteractSO();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ALB_NPC_Nurse::OnSOOneMontageEnded);
	AnimInst->Montage_SetEndDelegate(EndDelegate, Montage_One);
}

void ALB_NPC_Nurse::PlayAnimation_Two()
{
	if (!Montage_Two) return;

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (!AnimInst) return;

	float PlayTime = AnimInst->Montage_Play(Montage_Two);
	if (PlayTime <= 0.f) return;

	TimerOff_InteractSO();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ALB_NPC_Nurse::OnSOTwoMontageEnded);
	AnimInst->Montage_SetEndDelegate(EndDelegate, Montage_Two);
}

void ALB_NPC_Nurse::PlayAnimation_Three()
{
	if (!Montage_Three) return;

	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
	if (!AnimInst) return;

	float PlayTime = AnimInst->Montage_Play(Montage_Three);
	if (PlayTime <= 0.f) return;

	TimerOff_InteractSO();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ALB_NPC_Nurse::OnSOThreeMontageEnded);
	AnimInst->Montage_SetEndDelegate(EndDelegate, Montage_Three);
}

void ALB_NPC_Nurse::SOAction(FVector SOLocation, float ZRotation)
{
	if (!OwnerAICReference) return;
	if (LastSOAction < 0) return;

	OwnerAICReference->SetState_SmartObject(LastSOAction, SOLocation, ZRotation);
}

void ALB_NPC_Nurse::TimerOn_InteractSO()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(SOCheackTimerHandle, this, &ALB_NPC_Nurse::Check_SO, SO_CheckTime, true);
	}
}

void ALB_NPC_Nurse::TimerOff_InteractSO()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(SOCheackTimerHandle);
	}
}

void ALB_NPC_Nurse::SetStateInteract()
{
	if (!OwnerAICReference) return;

	OwnerAICReference->SetState_Interact();
}

void ALB_NPC_Nurse::SetStateNone()
{
	if (!OwnerAICReference) return;

	OwnerAICReference->SetState_None();
}

void ALB_NPC_Nurse::Resist_OwnerAIC()
{
	OwnerAICReference = Cast<ALB_AIC_Nurse>(GetController());

	if (IsValid(OwnerAICReference)) return;

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(OwnerAICResistTimerHandle, this, &ALB_NPC_Nurse::Resist_OwnerAIC, 1.0f, false);
	}
}

void ALB_NPC_Nurse::OnSOZeroMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != Montage_Zero) return;

	if (!bInterrupted)
	{
		SetStateNone();

		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SODelayTimerHandle, this, &ALB_NPC_Nurse::TimerOn_InteractSO, SO_DelayTime, false);
		}
	}
}

void ALB_NPC_Nurse::OnSOOneMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != Montage_One) return;

	if (!bInterrupted)
	{
		SetStateNone();

		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SODelayTimerHandle, this, &ALB_NPC_Nurse::TimerOn_InteractSO, SO_DelayTime, false);
		}
	}
}

void ALB_NPC_Nurse::OnSOTwoMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != Montage_Two) return;

	if (!bInterrupted)
	{
		SetStateNone();

		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SODelayTimerHandle, this, &ALB_NPC_Nurse::TimerOn_InteractSO, SO_DelayTime, false);
		}
	}
}

void ALB_NPC_Nurse::OnSOThreeMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != Montage_Three) return;

	if (!bInterrupted)
	{
		SetStateNone();

		if (GetWorld())
		{
			GetWorldTimerManager().SetTimer(SODelayTimerHandle, this, &ALB_NPC_Nurse::TimerOn_InteractSO, SO_DelayTime, false);
		}
	}
}

