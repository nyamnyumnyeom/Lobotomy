// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LBTargetPoint_Doctor.h"
#include "Components/SphereComponent.h"

ALBTargetPoint_Doctor::ALBTargetPoint_Doctor()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(180.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALBTargetPoint_Doctor::OnOverlapBegin);
}

void ALBTargetPoint_Doctor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			SpawnDoctorClass();
			DisableCollision();
		}
	}
}

void ALBTargetPoint_Doctor::SpawnDoctorClass()
{
	if (!DoctorClass) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FTransform SpawnTransform = GetActorTransform();

	FVector Location = SpawnTransform.GetLocation();
	Location.Z += 50.0f;
	SpawnTransform.SetLocation(Location);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	SpawnedDoctorClass= World->SpawnActor<AActor>(
		DoctorClass,
		SpawnTransform,
		SpawnParams
	);
}

void ALBTargetPoint_Doctor::DisableCollision()
{
	if (SphereCollision)
	{
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
