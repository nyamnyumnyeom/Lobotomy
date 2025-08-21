// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LB_NPCBase.generated.h"

UCLASS()
class LOBOTOMY_API ALB_NPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	ALB_NPCBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
