#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"
#include "UI/LB_ChartData.h"
#include "LB_GM.generated.h"

class ALB_Monster_ChainSawMan;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChartUpdated, int32, PageNumber);

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

	UFUNCTION(BlueprintCallable)
	void UpdateSet();

protected:
	virtual void BeginPlay() override;

	// ---------- 플레이어 게임 오버 ----------
public:
	// 플레이어 사망 로직 (TargetLocation : 바라볼 액터의 위치)
	void PlayerDeathLogic(FVector TargetLocation);

	// ---------- -------------------- ----------

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

	// ------------- 시간 -------------
protected:
	// 게임 내 시간
	int32 CurrentHour = 8;
	int32 CurrentMinute = 0;
	int32 CurrentSecond = 0; // 내부 계산용, UI에는 표시 X
	// 현실 1초당 게임 내 몇 초가 흐를지
	float TimeScale = 20.f;

	FTimerHandle TimeUpdateTimerHandle;

	void UpdateTimeByTimer();

public:
	// 시간 카운트 시작
	UFUNCTION(BlueprintCallable)
	void StartTimeCount();
	// 시간 카운트 중지
	UFUNCTION(BlueprintCallable)
	void StopTimeCount();

	// 현재 시/분 반환
	UFUNCTION(BlueprintCallable)
	void GetGameTime(int32& Hours, int32& Minutes) const;

	// 시간 설정
	UFUNCTION(BlueprintCallable)
	void SetGameTime(int32 Hour, int32 Minute);

	//----------------------------------------------------------------------------------테스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chart")
	UDataTable* ChartDataTable;

	/** 현재 페이지 번호 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	int32 CurrentPage = 0;

	/** 현재 페이지의 런타임 상태 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	FChartData CurrentChart;

	/** 페이지별 런타임 캐시 (수정사항 보존) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	TMap<int32, FChartData> RuntimeCharts;

	/** 페이지 로드(위젯 재생성 X, 값만 교체) */
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void LoadPage(int32 NewPage);

	/** 현재/특정 페이지 레코드 읽기 (복사본 반환) */
	UFUNCTION(BlueprintCallable, Category = "Chart")
	FChartData GetChartCopy(int32 Page) const;

	/** 현재 페이지 레코드 읽기(블루프린트 편의용) */
	UFUNCTION(BlueprintCallable, Category = "Chart")
	FChartData GetCurrentChartCopy() const { return CurrentChart; }

	/** 필드 수정 API(문자열 필드) */
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetNameForPage(int32 Page, const FString& NewName);
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetSymptomForPage(int32 Page, const FString& NewSymptom);
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetRemarkForPage(int32 Page, const FString& NewRemark);

	/** 체크박스 수정 */
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetDayCheckForPage(int32 Page, int32 DayIndex /*0~6*/, bool bChecked);

	/** 페이지/레코드 갱신 브로드캐스트 */
	UPROPERTY(BlueprintAssignable, Category = "Chart")
	FOnChartUpdated OnChartUpdated;

private:
	/** 캐시 없으면 DataTable에서 초기값 채워 캐시에 적재 */
	bool EnsurePageInCache(int32 Page);

	/** 내부 공통: 기록 갱신 후 CurrentChart/브로드캐스트 */
	void SyncCurrentFromCacheAndBroadcast();
};
