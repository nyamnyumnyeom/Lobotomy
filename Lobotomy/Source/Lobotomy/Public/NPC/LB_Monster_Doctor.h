// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "NPC/LB_NPCData.h"
#include "LB_Monster_Doctor.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_Monster_Doctor : public ALB_MonsterBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* SphereCollision;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> SpawnSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> NormalSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> FinishSounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Music")
	float SoundPlayDelay = 3.0f;

protected:
	FTimerHandle SoundPlayTimerHandle;
	FTimerHandle MonsterStateTimerHandle;

protected:
	AActor* CachedPlayerCharacter;


	EMonsterState CachedState;

public:
	ALB_Monster_Doctor();

protected:
	virtual void BeginPlay() override;

	virtual void StopMovemontAtDoor_Implementation() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponUp();

public:
	void SpawnLogic();

	void SetActorRotationToPlayer();

protected:
	// 재생시킬 소리의 종류를 매개변수로 입력.
	// 0: SpawnSounds
	// 1: NormalSounds
	// 2: FinishSounds
	void SoundPlay(int32 SoundType);

	void HeartbeatToggle(bool Value);

	void RestorationMonsterState();
};
