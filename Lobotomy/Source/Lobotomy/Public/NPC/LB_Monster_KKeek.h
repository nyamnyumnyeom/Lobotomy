// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "LB_Monster_KKeek.generated.h"

class UAudioComponent;
class USoundBase;

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_Monster_KKeek : public ALB_MonsterBase
{
	GENERATED_BODY()
	
protected:
	FVector OriginLocation;

protected:
	class ULB_KKeekComp* KKeekComp_Ref;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsWalkingRight = false;

	float WalkElapsedTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WalkDuration = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float NormalSpeed = 30.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RunawaySpeed = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PlayerKillDistance = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RightOffset = 100.f;

protected:
	UPROPERTY()
	UAudioComponent* VisibleAudioComp;

	UPROPERTY()
	UAudioComponent* SideWalkAudioComp;

	UPROPERTY()
	UAudioComponent* RunawayAudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase*> VisibleSoundCues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase*> SideWalkSoundCues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase*> RunawaySoundCues;

protected:
	FTimerHandle ResistTimerHandle;
	FTimerHandle AutoInvisibleTimerHandle;

public:
	ALB_Monster_KKeek();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	// 끽끽이 사라지는 로직.
	// Visibility, Collision, Movement 끄고 원래 위치(배치된 위치)로 이동.
	UFUNCTION(BlueprintCallable)
	void KKeekKKeekInvisible();

	// 끽끽이 등장하는 로직.
	// Visibility, Collision, Movement 켜고 NewLocation으로 이동.
	UFUNCTION(BlueprintCallable)
	void KKeekKKeekVisible(FVector NewLocation);

	// 끽끽이가 플레이어를 응시하는 로직.
	// 제자리에 멈춰서 플레이어를 바라봄.
	UFUNCTION(BlueprintCallable)
	void KKeekKKeekWatchThePlayer();

	// 킬 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* PlayMontage;

	// 응시 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* WatchMontage;

	// 몽타주 재생 함수
	UFUNCTION(BlueprintCallable)
	void PlayKillMontage(float PlayRate = 1.0f);

protected:
	void ResistForPlayer();

	void MoveToFarthestReachableTarget();

	void KKERealInvisible();

protected:
	void PlaySound_Visible();

	void PlaySound_Runaway();
};
