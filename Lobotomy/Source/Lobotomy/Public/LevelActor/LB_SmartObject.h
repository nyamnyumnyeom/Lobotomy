// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "NPC/Interface/LB_Interface_SmartObject.h"
#include "LB_SmartObject.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_SmartObject : public ATargetPoint, public ISO_Nurse
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* SphereCollision;

public:
	// 간호사가 해당 오브젝트에 도달해 SmartObject 로직이 실행되는 경우 어떤 행동을 취하게 할지.
	// 0 : 허리에 손을 올린 채로 벽을 응시.
	// 1 : 팔짱을 낀 채로 책상 등을 응시.
	// 2 : 문을 두드린 후 열어봄.
	// 3 : 환자와 대화를 시도함.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "For Nurse")
	int32 NurseSOAction = 0;

public:
	ALB_SmartObject();

public:
	// Smart Object에서 호출될 인터페이스 함수. 
	// 간호사에게 어떤 행동을 해야할지 알려주는 용도.
	virtual int32 CheakNurseSOAction_Implementation() override;

};
