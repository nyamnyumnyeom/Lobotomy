// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_PatientBase.h"
#include "NPC/AI/LB_AICPatientBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

ALB_PatientBase::ALB_PatientBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SleepAtBedBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SleepAtBedBillboard->SetupAttachment(RootComponent);
	SleepAtBedBillboard->SetRelativeLocation(FVector(0.0f, 0.0f, -98.0f));

	SleepAtBedArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ChainSawManSpawnPoint"));
	SleepAtBedArrow->SetupAttachment(SleepAtBedBillboard);

	Tags.Add(FName("Patient"));
}

void ALB_PatientBase::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		OriginLocation = MeshComp->GetComponentLocation();
		OriginRotator = MeshComp->GetComponentRotation();

		BedLocation = SleepAtBedBillboard->GetComponentLocation();
		BedRotation = SleepAtBedBillboard->GetComponentRotation() + FRotator(0.0f, -90.0f, 0.0f);

		CachedActorLocation = GetActorLocation();
		CachedActorRotator = GetActorRotation();

	}
}

void ALB_PatientBase::ApplyAnimBlueprint(int32 Index)
{
	if (AnimBlueprintPresets.Num() == 0) return;

	TSubclassOf<UAnimInstance> SelectedAnimBP = AnimBlueprintPresets[Index];

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp && SelectedAnimBP)
	{
		MeshComp->SetAnimInstanceClass(SelectedAnimBP);

	}
}

void ALB_PatientBase::OnNightBehavior()
{
	ApplyAnimBlueprint(4);

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		CachedActorLocation = GetActorLocation();
		CachedActorRotator = GetActorRotation();

		SetActorLocation(BedLocation + FVector(0.0f, 0.0f, 98.0f));
		SetActorRotation(BedRotation);

		MeshComp->SetWorldLocation(BedLocation);
		MeshComp->SetWorldRotation(BedRotation);
	}
}

void ALB_PatientBase::OnNightBehaviorHint()
{
	ApplyAnimBlueprint(Behnum);

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		CachedActorLocation = GetActorLocation();
		CachedActorRotator = GetActorRotation();

		SetActorLocation(BedLocation + FVector(0.0f, 0.0f, 98.0f));
		SetActorRotation(BedRotation);

		MeshComp->SetWorldLocation(BedLocation);
		MeshComp->SetWorldRotation(BedRotation);
	}
}

void ALB_PatientBase::SetInteractState()
{
	ALB_AICPatientBase* AIC = Cast<ALB_AICPatientBase>(GetController());
	if (AIC)
	{
		AIC->SetState_Interact();
	}
}

void ALB_PatientBase::SetOriginState()
{
	ALB_AICPatientBase* AIC = Cast<ALB_AICPatientBase>(GetController());
	if (AIC)
	{
		if (BehaviorMode == 1)
		{
			AIC->SetState_Strafe();
		}
		else
		{
			AIC->SetState_None();
		}
	}
}

void ALB_PatientBase::OnDayBehavior(bool bIsWalker)
{
	ApplyAnimBlueprint(BehaviorMode);

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		FVector NewLocation = OriginLocation;
		FRotator NewRotator = OriginRotator;

		SetActorLocation(CachedActorLocation);
		SetActorRotation(CachedActorRotator);

		if (bIsWalker)
		{
			NewLocation = GetActorLocation() + FVector(0.0f, 0.0f, -88.0f);
			NewRotator = GetActorRotation() + FRotator(0.0f, -90.0f, 0.0f);
		}

		MeshComp->SetWorldLocation(NewLocation);
		MeshComp->SetWorldRotation(NewRotator);
	}
}
