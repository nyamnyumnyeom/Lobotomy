// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_MonsterBase.h"

ALB_MonsterBase::ALB_MonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Monster"));
}

bool ALB_MonsterBase::CheakShouldDestroy_Implementation()
{
	return false;
}

void ALB_MonsterBase::DisappearLogic()
{

}