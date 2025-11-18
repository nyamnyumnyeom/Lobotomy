// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_PatientBase.h"
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

	FVector BedLocation = SleepAtBedBillboard->GetComponentLocation();

	FRotator BedRotation = SleepAtBedBillboard->GetComponentRotation() + FRotator(0.0f, -90.0f, 0.0f);

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		MeshComp->SetWorldLocation(BedLocation);
		MeshComp->SetWorldRotation(BedRotation);
	}
}

void ALB_PatientBase::OnDayBehavior()
{
	ApplyAnimBlueprint(BehaviorMode);

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp)
	{
		FVector NewLocation;
		FRotator NewRotation;

		if (OriginLocation == FVector::ZeroVector)
		{
			NewLocation = GetActorLocation();
		}
		else
		{
			NewLocation = OriginLocation;
		}

		if (OriginRotator == FRotator::ZeroRotator)
		{
			NewRotation = GetActorRotation();
		}
		else
		{
			NewRotation = OriginRotator;
		}

		MeshComp->SetWorldLocation(NewLocation);
		MeshComp->SetWorldRotation(NewRotation);
	}
}
