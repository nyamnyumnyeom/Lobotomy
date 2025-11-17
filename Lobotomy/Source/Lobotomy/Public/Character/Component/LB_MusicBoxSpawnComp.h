// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LB_MusicBoxSpawnComp.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API ULB_MusicBoxSpawnComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// 플레이어 캐릭터 기준 타겟 포인트를 검사할 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SphereTraceRadius = 1000.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float Threshold = 0.5f;

public:	
	ULB_MusicBoxSpawnComp();

protected:
	virtual void BeginPlay() override;

public:
	// 오르골을 스폰해야 하는 조건이 충족되면 이 함수를 실행하면 됨.
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TriggerMusicBoxSpawn();

};
