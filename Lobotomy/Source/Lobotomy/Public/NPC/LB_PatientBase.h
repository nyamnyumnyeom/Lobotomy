// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_NPCBase.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "LB_PatientBase.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_PatientBase : public ALB_NPCBase
{
	GENERATED_BODY()

public:
	// 밤에 이동할 침대의 위치.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UBillboardComponent* SleepAtBedBillboard;

	// 밤에 이동할 침대의 위치. (화살표)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UArrowComponent* SleepAtBedArrow;

public:
	// 순서대로 저장 필수 [0 : 서있기-Stand], [1 : 배회하기-Strafe], [2 : 앉아있기-Sit], [3 : 누워있기-Lay], [4 : 잠자기-Sleep]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<TSubclassOf<UAnimInstance>> AnimBlueprintPresets;

	// [0:서있기 - Stand] , [1:배회하기 - Strafe], [2:앉아있기 - Sit], [3:누워있기 - Lay], [4:잠자기 - Sleep]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	int32 BehaviorMode = 0;

protected:
	FVector CachedActorLocation = FVector::ZeroVector;
	FRotator CachedActorRotator = FRotator::ZeroRotator;

	FVector OriginLocation = FVector::ZeroVector;
	FRotator OriginRotator = FRotator::ZeroRotator;

	FVector BedLocation = FVector::ZeroVector;
	FRotator BedRotation = FRotator::ZeroRotator;

public:
	ALB_PatientBase();

protected:
	virtual void BeginPlay() override;

public:
	// [0:서있기 - Stand] , [1:배회하기 - Strafe], [2:앉아있기 - Sit], [3:누워있기 - Lay], [4:잠자기 - Sleep]
	UFUNCTION(BlueprintCallable)
	void ApplyAnimBlueprint(int32 Index);

	// 밤이 되었을 때 실행시킬 함수. 지정한 위치로 이동 + 애니메이션 프리셋을 잠자기로 변경함.
	UFUNCTION(BlueprintCallable)
	void OnNightBehavior();

	UFUNCTION(BlueprintCallable)
	void OnNightBehaviorHint();

	UFUNCTION(BlueprintCallable)
	void SetInteractState();

	UFUNCTION(BlueprintCallable)
	void SetOriginState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	int32 Behnum;

	// 낮이 되었을 때 실행시킬 함수. 기존 위치로 이동 + 애니메이션 프리셋을 초기 값으로 변경함.
	UFUNCTION(BlueprintCallable)
	void OnDayBehavior(bool bIsWalker);
};
