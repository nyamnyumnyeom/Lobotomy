// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "LB_TargetPoint_MusicBox.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_TargetPoint_MusicBox : public ATargetPoint
{
	GENERATED_BODY()

public:
	// 전기톱 살인마 스폰 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UBillboardComponent* ChainSawManBillboard;

	// 전기톱 살인마 스폰 위치 (화살표)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UArrowComponent* ChainSawManSpawnPoint;

	// 오르골 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> MusicBoxClass;

	// 전기톱 살인마 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ChainSawManClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float TimeupTime = 20.0f;

protected:
	FTimerHandle MusicBoxTimerHandle;
	FTimerHandle MusicBoxDestroyTimerHandle;

protected:
	UPROPERTY()
	class ALB_MusicBox* SpawnedMusicBox;

public:
	ALB_TargetPoint_MusicBox();

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void MusicBoxSystemActivate();

	// MusicBox에서 타이머 클리어 요청
	void StopMusicBoxTimer();

protected:
	// 제한시간이 종료되어 이벤트 발동
	void MusicBoxTimeup();

	// 모든 역할이 끝나서 제거 시도
	void TryMusicBoxDestroy();

};
