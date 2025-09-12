// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LB_HideAndSeekComp.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOBOTOMY_API ULB_HideAndSeekComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// 플레이어 캐릭터 기준 타겟 포인트를 검사할 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SearchRadius = 1500.0f;

protected:
	bool bIsPlayerOutDoor;

protected:
	FTimerHandle TriggerLoopTimerHandle;

public:	
	ULB_HideAndSeekComp();

protected:
	virtual void BeginPlay() override;
		
public:
	// 숨바꼭질 장인을 스폰해야 하는 조건이 충족되면 이 함수를 실행하면 됨.
	// 근처에 스폰할 타겟 포인트가 없다면 1초마다 재검사해 로직 실행을 시도함.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerHASSpawn();

	// TriggerHASSpawn() 함수를 작동시키기 전에 실행해야 하는 함수.
	// 플레이어가 문 기준 안쪽(방)에서 실행할 경우 false,
	// 플레이어가 문 기준 바깥쪽(복도)에서 실행할 경우 true.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	FORCEINLINE void SetIsPlayerOutDoor(bool IsPlayerOutDoor) { bIsPlayerOutDoor = IsPlayerOutDoor; }

protected:
	class ALB_TargetPoint_HAS* FindNearestHAS();
};
