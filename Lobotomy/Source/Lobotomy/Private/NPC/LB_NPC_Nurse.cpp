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

				SOAction();
			}
		}
	}
}

void ALB_NPC_Nurse::SOAction()
{
	if (!OwnerAICReference) return;
	if (LastSOAction < 0) return;

	OwnerAICReference->SetState_SmartObject(LastSOAction);
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

void ALB_NPC_Nurse::Resist_OwnerAIC()
{
	OwnerAICReference = Cast<ALB_AIC_Nurse>(GetController());

	if (IsValid(OwnerAICReference)) return;

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(OwnerAICResistTimerHandle, this, &ALB_NPC_Nurse::Resist_OwnerAIC, 1.0f, false);
	}
}

