// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "LB_TargetPoint_TeddyBear.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_TargetPoint_TeddyBear : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Components")
	class UStaticMeshComponent* LampMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Components")
	class USpotLightComponent* SpotLightComponent;

	// 곰괴물 스폰 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UBillboardComponent* MonsterSpawnBillboard;

	// 곰괴물 스폰 위치 (화살표)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UArrowComponent* MonsterSpawnPoint;

public:	
	// 빛이 밝아졌을 때의 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB|Light Settings")
	float DayIntensity;

	// 빛이 어두워졌을 때의 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB|Light Settings")
	float NightIntensity;

	// 곰괴물 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> MonsterBearClass;

public:
	// 곰인형이 랜덤 이동하여 해당 타깃포인트에 위치한 상태인가?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Property")
	bool bIsBearHere = false;

	// 곰인형 레퍼런스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Property")
	class ALB_TeddyBear* TeddyBear_Ref;

	// 곰괴물 레퍼런스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Property")
	class ALB_Monster_TeddyBear* MonsterBear_Ref;

public:
	ALB_TargetPoint_TeddyBear();

protected:
	virtual void BeginPlay() override;

public:
	// 밤/낮 라이트 조절 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Action")
	void TriggerLightEffect(bool bIsNight);

public:
	// 곰인형 나타나는 연출
	UFUNCTION(BlueprintCallable)
	void ShowTeddyBear();

	// 전등 깜박거리기 (곰인형)
	UFUNCTION(BlueprintImplementableEvent)
	void OnTeddyBearShow();

	// 상호작용 위젯 숨기기
	UFUNCTION(BlueprintCallable)
	void InteractWidgetHide();

	// 곰인형 보이기
	UFUNCTION(BlueprintCallable)
	void TeddyBearSetVisibility(bool Visibility);

	// 곰인형 콜리전
	UFUNCTION(BlueprintCallable)
	void TeddyBearSetActiveCollision(bool Collision);

public:
	// 전등 깜박거리기 (괴물곰)
	UFUNCTION(BlueprintImplementableEvent)
	void OnMonsterBearShow();
	
	// 괴물곰 스폰
	UFUNCTION(BlueprintCallable)
	void SpawnMonsterBear();

public:
	// 곰인형 레퍼런스 등록 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void ReferenceResister(ALB_TeddyBear* TeddyBearClass);

	// 곰인형 레퍼런스 초기화 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void ReferenceClear();

	// 곰인형 체크 함수
	//UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	//bool GetbIsBearHere();

	// 곰인형 불러오기 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void GetBearHere();
};
