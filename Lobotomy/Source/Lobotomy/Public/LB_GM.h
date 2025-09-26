#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LB_GM.generated.h"

class ALB_Monster_ChainSawMan;

UCLASS()
class LOBOTOMY_API ALB_GM : public AGameMode
{
	GENERATED_BODY()
	
	// ---------- 몬스터 스폰 상태 ----------
protected:
	// 스폰중인 전기톱 살인마 레퍼런스
	TWeakObjectPtr<ALB_Monster_ChainSawMan> ChainSawManRef;

	// 숨바꼭질 장인이 스폰되어 있는가?
	bool bIsHidAndSeekerSpawned = false;

	// 전기톱 살인마가 스폰되어 있는가?
	bool bIsChainSawManSpawned = false;

	// 숨바꼭질 장인이 문을 해당 숫자 이상 두드릴 때부터 전기톱 스폰 확률 생김
	int32 PatienceLimit = 3;
	// 숨바꼭질 장인이 문을 두드린 횟수
	int32 KnockCount = 0;
	// 숨바꼭질 장인의 다음 노크에 전기톱 살인마를 스폰시켜야 하는가?
	bool ShouldChainSawManSpawn = false;

	// ---------- -------------------- ----------

public:
	ALB_GM();

protected:
	virtual void BeginPlay() override;


	// ---------- 숨바꼭질 장인 관련 함수 ----------
public:
	// 숨바꼭질 장인이 노크한 횟수 증가
	void AddKnockCount();

	// 숨바꼭질 장인이 노크한 횟수 초기화
	void ResetKnockCount();

	// 숨바꼭질 장인 스폰 여부 설정
	FORCEINLINE void SetIsHidAndSeekerSpawned(bool Value) { bIsHidAndSeekerSpawned = Value; }

	// 숨바꼭질 장인이 스폰되어 있는가?
	FORCEINLINE bool GetIsHidAndSeekerSpawned() const { return bIsHidAndSeekerSpawned; }
	// ---------- -------------------- ----------
	
	// ---------- 전기톱 살인마 관련 함수 ----------
public:
	// 전기톱 살인마 스폰 여부 설정
	FORCEINLINE void SetIsChainSawManSpawned(bool Value) { bIsChainSawManSpawned = Value; }

	// 전기톱 살인마 레퍼런스 등록
	FORCEINLINE void SetChainSawManRef(TWeakObjectPtr<ALB_Monster_ChainSawMan> CSM) { ChainSawManRef = CSM; }

	// 전기톱 살인마 위치 재설정
	void SetChainSawManTransform(FTransform NewTransform);


	// 전기톱 살인마가 개빡친 상황인가?
	FORCEINLINE bool GetShouldChainSawManSpawn() const { return ShouldChainSawManSpawn; }

	// 전기톱 살인마가 스폰되어 있는가?
	FORCEINLINE bool GetIsChainSawManSpawned() const { return bIsChainSawManSpawned; }

	// 전기톱 살인마가 플레이어와 내비메시 길찾기 경로상 얼만큼 떨어져 있는가?
	float GetChainSawManToPlayerDistance();
	// ---------- -------------------- ----------

	// ------------- 날짜 & 밤낮 ---------
public:
	// 현재 날짜 (1일부터 시작)
	int32 CurrentDay = 1;

	// 낮/밤 여부 (true = 밤, false = 낮)
	bool bIsNight = false;

	void UpdateDate();

	// 날짜 초기화 (1일로)
	void ClearDate();

	// 낮 → 밤
	void ChangeToNight();

	// 밤 → 낮
	void ChangeToDay();

	// Getter
	FORCEINLINE int32 GetCurrentDay() const { return CurrentDay; }
	FORCEINLINE bool IsNight() const { return bIsNight; }
};
