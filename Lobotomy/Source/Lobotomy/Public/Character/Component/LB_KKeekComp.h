// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LB_KKeekComp.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API ULB_KKeekComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// 끽끽이 첫 등장 거리.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float FirstSpawn_Length = 700.0f;

	// 끽끽이 등장시마다 감소시킬 거리. 해당 수치에 현재 진행된 날짜를 곱하여 계산.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float Spawn_Length_Closer = 20.0f;

	// 끽끽이 공격 거리.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float CanAttack_Length = 100.0f;

	// 재등장이 가능하기까지의 대기 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float Action_WaitTime = 60.0f;

	// 플레이어가 끽끽이를 바라보는 내적이 해당 값 이상일 때 사라짐.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float Threshold = 0.0f;

	// 재등장이 가능하지 않은 대기 시간인가?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	bool bIsWaiting = false;

	// 등장 로직을 실행시켜 끽끽이가 플레이어 근처로 이동했는지.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LB_Property|State")
	bool bIsKKeekHere = false;

	// 사라져야 하는 조건이 거리가 너무 멀어져서인지.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LB_Property|State")
	bool bIsTooFar = false;

protected:
	float CurrentSpawn_Length = FirstSpawn_Length;

	FVector CanActiveLocation;

protected:
	class ALB_Monster_KKeek* KKeek_Ref;

protected:
	FTimerHandle TriggerLoopTimerHandle;
	FTimerHandle WaitingTimerHandle;
	FTimerHandle DissapearTimerHandle;

public:
	ULB_KKeekComp();

protected:
	virtual void BeginPlay() override;

public:
	// 끽끽이 로직 조건검사 (블루프린트 전용)
	UFUNCTION(BlueprintImplementableEvent, Category = "Spawn")
	void CheakKKeekCondition();

	// 끽끽이 로직을 실행해야 하는 타이밍에 이 함수를 호출.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerKKeek();

	// 끽끽이 사라지게 해야 하는 타이밍에 이 함수를 호출.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DissapearKKeek();

	// 끽끽이 로직을 실행할 수 있는 조건인지 검사.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	bool CheckCanActive();

	// 끽끽이 사라지게 할 수 있는 조건인지 검사.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void CheckCanDissapear();

	// 끽끽이 로직 조건검사 (블루프린트 전용)
	UFUNCTION(BlueprintImplementableEvent, Category = "Spawn")
	void CheckCanDissapearBP();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DissapearCheckTimerStart();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DissapearCheckTimerClear();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerLoopTimerStart();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerLoopTimerClear();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void WaitingTimer();

	// 거리 초기화
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DistanceReset();

public:
	void ResistKKeek(class ALB_Monster_KKeek* Ref);

protected:
	void SetWaitingFalse();
};
