// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "LB_Monster_TeddyBear.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_Monster_TeddyBear : public ALB_MonsterBase
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
	bool bIsSpawnDurationOver = false;

protected:
	FTimerHandle SpawnDurationTimerHandle;

protected:
	AActor* CachedPlayerCharacter;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* SpawnSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* KillSoundCue;

public:
	ALB_Monster_TeddyBear();

	virtual bool CheakShouldDestroy_Implementation() override;

	virtual void DisappearLogic() override;

	void	SetActorRotationToPlayer();

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

protected:
	void TimeupSpawnDuration();

	void SetSpawnWhetherToGM(bool Value);

protected:
	void PlaySound_Spawn();

	void PlaySound_Kill();
};
