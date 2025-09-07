// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_PatientBase.h"

ALB_PatientBase::ALB_PatientBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Patient"));
}
