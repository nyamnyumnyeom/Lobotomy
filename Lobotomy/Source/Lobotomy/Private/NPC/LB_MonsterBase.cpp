// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_MonsterBase.h"

ALB_MonsterBase::ALB_MonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("Monster"));
}
