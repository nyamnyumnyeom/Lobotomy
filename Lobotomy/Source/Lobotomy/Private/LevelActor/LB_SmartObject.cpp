// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActor/LB_SmartObject.h"
#include "Components/SphereComponent.h"

ALB_SmartObject::ALB_SmartObject()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->InitSphereRadius(300.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Tags.Add(FName("SmartObject"));
}

int32 ALB_SmartObject::CheakNurseSOAction_Implementation()
{
	return NurseSOAction;
}
