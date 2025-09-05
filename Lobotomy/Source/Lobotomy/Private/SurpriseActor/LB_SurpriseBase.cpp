// Fill out your copyright notice in the Description page of Project Settings.


#include "SurpriseActor/LB_SurpriseBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ALB_SurpriseBase::ALB_SurpriseBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->InitSphereRadius(500.f);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// Static Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALB_SurpriseBase::OnSphereOverlap);

}

void ALB_SurpriseBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALB_SurpriseBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("Player")) return;

	SurprisEventStart();
}

void ALB_SurpriseBase::SurprisEventStart()
{
	// 자식 클래스에서 재정의
}

