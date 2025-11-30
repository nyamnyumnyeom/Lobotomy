// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "LB_TargetPoint_HAS.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_TargetPoint_HAS : public ATargetPoint
{
	GENERATED_BODY()

public:
	// 방 안에서 스폰시 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UBillboardComponent* InsideBillboard;

	// 방 안에서 스폰시 위치 (화살표)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UArrowComponent* InsideSpawnPoint;

	// 숨바꼭질 장인 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> HideAndSeekerClass;

	// 전기톱 살인마 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ChainSawManClass;

	// 전기톱 살인마를 스폰해야 하는 타이밍에 이미 레벨에 있다면, 내비경로 기준 얼만큼 떨어져 있어야 위치를 변경시킬지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float RespawnDistance = 1000.0f;

	// 노커가 3번 인사한 뒤 4번째 스폰시 플레이어 후방에 스폰할 때 거리 오프셋 설정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float AnglyKnockerDistanceOffset = 100.0f;

	// 노커가 3번 인사한 뒤 4번째 스폰시 플레이어 후방에 스폰할 때 높이 오프셋 설정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float AnglyKnockerZOffset = 0.0f;

protected:
	bool bIsAttack = false;

protected:
	FTimerHandle HASTimerHandle;
	FTimerHandle HASDestroyTimerHandle;

protected:
	UPROPERTY()
	class ALB_MonsterHideAndSeeker* SpawnedHideAndSeeker;

	UPROPERTY()
	class ALB_Monster_ChainSawMan* SpawnedChainSawMan;

public:
	ALB_TargetPoint_HAS();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void HASSystemActivate(bool bIsOutDoor);

protected:
	void SpawnLogic(TSubclassOf<AActor> SpawnClass, bool bIsOutDoor);

	bool CheckNearbyDoorOpened();
};
