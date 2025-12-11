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

public:	
	// 빛이 밝아졌을 때의 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB|Light Settings")
	float DayIntensity;

	// 빛이 어두워졌을 때의 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB|Light Settings")
	float NightIntensity;

public:
	// 곰인형이 랜덤 이동하여 해당 타깃포인트에 위치한 상태인가?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Property")
	bool bIsBearHere = false;

	// 곰인형 레퍼런스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LB|Property")
	class ALB_TeddyBear* TeddyBear_Ref;

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
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void ShowTeddyBear();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTeddyBearShow();

public:
	// 곰인형 레퍼런스 등록 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void ReferenceResister(ALB_TeddyBear* TeddyBearClass);

	// 곰인형 레퍼런스 초기화 함수
	UFUNCTION(BlueprintCallable, Category = "LB|Reference")
	void ReferenceClear();
};
