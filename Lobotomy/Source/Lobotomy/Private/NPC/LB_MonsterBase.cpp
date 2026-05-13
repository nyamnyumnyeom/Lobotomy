// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_MonsterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/LB_Character.h"

ALB_MonsterBase::ALB_MonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Monster"));
}

bool ALB_MonsterBase::CheakShouldDestroy_Implementation()
{
	return false;
}

void ALB_MonsterBase::CheckIsChase_Implementation(bool bIsChase)
{
}

void ALB_MonsterBase::StopMovemontAtDoor_Implementation()
{

}

void ALB_MonsterBase::DisappearLogic()
{

}

void ALB_MonsterBase::Sanity_Reduces(float Amount)
{
	ALB_Character* LB_Character = Cast<ALB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!LB_Character) return;

	LB_Character->ReduceSanity(Amount);
}

bool ALB_MonsterBase::CheakPlayerIsIn()
{
	ALB_Character* LB_Character = Cast<ALB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (LB_Character)
	{
		FProperty* Property = LB_Character->GetClass()->FindPropertyByName(FName("Isin?"));

		if (Property)
		{
			FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property);
			if (BoolProperty)
			{
				bool bCurrentValue = BoolProperty->GetPropertyValue_InContainer(LB_Character);

				if (bCurrentValue) return true;
			}
		}
	}

    return false;
}
