// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "LB_Monster_ChainSawMan.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_Monster_ChainSawMan : public ALB_MonsterBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* SphereCollision;

public:
	// 스폰 후 유지 가능한 최소 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float SpawnDuration = 60.0f;

protected:
	// 스폰 유지 시간이 초과되었는가?
	bool bIsSpawnDurationOver = false;

	bool bIsChasing = false;
	bool bIsRunning = false;
	float CurrentSpeed = 150.0f;

protected:
	FTimerHandle SpawnDurationTimerHandle;
	FTimerHandle SpeedSettingTimerHandle;
	FTimerHandle RunModeTimerHandle;

protected:
	AActor* CachedPlayerCharacter;

public:
	ALB_Monster_ChainSawMan();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	virtual bool CheakShouldDestroy_Implementation() override;

	virtual void CheckIsChase_Implementation(bool bIsChase) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponUp();

public:
	void SpawnLogic();

	void SetActorRotationToPlayer();

	virtual void DisappearLogic() override;

protected:
	void SetSpawnWhetherToGM(bool Value);

	void TimeupSpawnDuration();

	void SpeedSettingTimer();
	void SpeedApply();
	void SpeedReset();
};
