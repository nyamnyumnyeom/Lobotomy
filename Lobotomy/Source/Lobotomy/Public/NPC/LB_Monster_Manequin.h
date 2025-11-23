// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/LB_MonsterBase.h"
#include "Sound/SoundCue.h"
#include "LB_Monster_Manequin.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_Monster_Manequin : public ALB_MonsterBase
{
	GENERATED_BODY()
	
public: 
	// 조우시 재생시킬 사운드.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	 USoundCue* SoundCue_Meet;

	 // 순간이동시 재생시킬 사운드.
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	 USoundCue* SoundCue_Disappear;


	// ABP에 적용된 Pose의 총 갯수.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|Pose")
	int32 NumOfPose = 0;

	// 따라붙기 시작한 뒤, 일정 시간 뒤에 다른 위치로 순간이동하고 초기화되기까지 최소 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float Manequin_ResetTime_Min = 60.0f;

	// 따라붙기 시작한 뒤, 일정 시간 뒤에 다른 위치로 순간이동하고 초기화되기까지 최대 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|State")
	float Manequin_ResetTime_Max = 100.0f;

	// 벽을 끼고 사야를 벗어날 경우, 일정 시간 뒤에 움직임을 재개하는 최소 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|Move")
	float MoveRestartTime_Min = 10.0f;

	// 벽을 끼고 사야를 벗어날 경우, 일정 시간 뒤에 움직임을 재개하는 최대 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LB_Property|Move")
	float MoveRestartTime_Max = 30.0f;

protected:
	// Reference
	ACharacter* PlayerCharacterReference_C;

	class ALB_AICMonster_Manequin* OwnerAICReference;

	// State
	bool bIsAwake = false;

	bool bIsPlayerEyesOnMe = true;

	bool bCanMoveRestartTimer = true;

	bool bCanPoseChangeTimer = true;

	bool bShouldReset = false;

	// Pose
	int32 Pose_Index = 0;

	// Sound
	bool bIsMeetSound_Played = false;

protected:
	FTimerHandle PlayerResistTimerHandle;
	FTimerHandle OwnerAICResistTimerHandle;

	FTimerHandle ManequinRestartTimerHandle;

	FTimerHandle MoveRestartTimerHandle;
	FTimerHandle PoseChangeTimerHandle;

public:
	ALB_Monster_Manequin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Manequin_Awake();

	bool IsPlayerLookingAtMe(float Threshold = 0.0f);

	UFUNCTION(BlueprintImplementableEvent)
	void PoseChange(int32 Index);

	// Resist
public:
	void Resist_PlayerCharacter_C();
	void Resist_OwnerAIC();

	// Pose
protected:
	void SetRandomPose();
	void RandomPose_Restart();

	// State
protected:
	void SetManequinResetLogic();
	void ManequinReset();

	void Reset_Apply();

	bool TeleportToRandomNavLocation(float MinDistanceFromPlayer = 3000.0f, float SearchRadius = 5000.0f, int32 MaxAttempts = 3);
	bool IsVisibleTime();

	// Move
protected:
	void Manequin_MoveLogic();
	void Manequin_StopLogic();

	void Manequin_Move_Restart();

protected:
	void PlaySound_Manequin(USoundCue* Sound, FVector SoundLocation);

public:
	FORCEINLINE bool GetbIsPlayerEyesOnMe() const { return bIsPlayerEyesOnMe; }
	FORCEINLINE int32 GetPoseIndex() const { return Pose_Index; }
};
