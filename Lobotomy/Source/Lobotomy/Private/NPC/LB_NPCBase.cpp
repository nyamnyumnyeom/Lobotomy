// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_NPCBase.h"

ALB_NPCBase::ALB_NPCBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("NPC"));
}

void ALB_NPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALB_NPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}