// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_TeddyBear.generated.h"

UCLASS()
class LOBOTOMY_API ALB_TeddyBear : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Components")
	class UStaticMeshComponent* TeddyMeshComponent;

public:
	// 상호작용시 괴물 곰이 등장할 백분율.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB|Properties")
	int32 MonsterPercentage = 10;

	UPROPERTY(BlueprintReadWrite, Category = "LB|Value")
	bool bIsCheckTonight = false;

protected:
	FVector OriginLocation;
	FRotator OriginRotator;

	class ALB_TargetPoint_TeddyBear* TargetPoint_Ref;

public:
	ALB_TeddyBear();

protected:
	virtual void BeginPlay() override;

public:
	// bShouldMonster가 true면 괴물 곰이 등장하도록 해야 함.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void CheckMonsterPercentage(bool &bShouldMonster);

public:
	// 괴물화 전등 연출 함수.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void MonsterLightDirected();

public:
	// bIsActive가 true면 보임, false면 안 보임.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void SetBearVisibility(bool bIsActive);

	// bIsActive가 true면 충돌 가능, false면 충돌 없음.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void SetBearCollision(bool bIsActive);

	// 레벨에 배치된 ALB_TargetPoint_TeddyBear 중 하나로 랜덤 이동.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void TeleportToRandomTarget();

	// 레벨에 배치된 ALB_TargetPoint_TeddyBear 에서 호출하는 곳으로 이동.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void TeleportToSpecialTarget(ALB_TargetPoint_TeddyBear* TP);

public:
	// 원래 위치로 이동.
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void TeleportToOrigin();

	// 타깃포인트 레퍼런스 초기화 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void ReferenceClear();

	// 상호작용 위젯 숨기기
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractWidgetHide();

protected:
	void SetSpawnWhetherToGM(bool Value);
};
