#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"
#include "UI/LB_ChartData.h"
#include "NPC/LB_Monster_ChainSawMan.h"
#include "LB_GM.generated.h"

class ULB_DialogueUI;
class UDataTable;
class ALB_Monster_TeddyBear;
class ALB_TeddyBear;
class ALB_Monster_Manequin;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChartUpdated, int32, PageNumber);

UCLASS()
class LOBOTOMY_API ALB_GM : public AGameMode
{
	GENERATED_BODY()

	// ---------- 몬스터 스폰 상태 ----------
protected:
	// 스폰중인 전기톱 살인마 레퍼런스
	ALB_Monster_ChainSawMan* ChainSawManRef;

	// 스폰중인 곰탱이 레퍼런스
	ALB_Monster_TeddyBear* TeddyBearRef;

	// 스폰중인 곰탱이 인형 레퍼런스
	ALB_TeddyBear* TeddyRef;

	// 스폰중인 마네킹 레퍼런스
	ALB_Monster_Manequin* ManequinRef;

	// 숨바꼭질 장인이 스폰되어 있는가?
	bool bIsHidAndSeekerSpawned = false;

	// 전기톱 살인마가 스폰되어 있는가?
	bool bIsChainSawManSpawned = false;

	// 숨바꼭질 장인이 문을 해당 숫자 이상 두드릴 때부터 전기톱 스폰 확률 생김
	int32 PatienceLimit = 1;
	// 숨바꼭질 장인이 문을 두드린 횟수
	int32 KnockCount = 0;
	// 숨바꼭질 장인의 다음 노크에 전기톱 살인마를 스폰시켜야 하는가?
	//bool ShouldChainSawManSpawn = false;
	// 다음 노크에 문을 열어야 하는가?
	bool ShouldOpenDoor = false;

	// 숨바꼭질 장인이 문을 해당 숫자 이상 인사하면 이후 스폰은 플레이어 공격
	int32 HelloLimit = 1;
	// 숨바꼭질 장인이 문을 두드린 횟수
	int32 HelloCount = 0;
	// 숨바꼭질 장인의 다음 스폰에 플레이어를 공격해야 하는가?
	bool ShouldHASAttackMode = false;

	// 금고 실패시 경보가 해당 횟수 이상 울리면 전기톱 스폰.
	int32 SafeBoxAlertLimit = 2;
	// 금고 실패시 경보가 울린 횟수.
	int32 SafeBoxAlertCount = 0;
	// 다음 금고 실패시 경보가 울리고 전기톱을 스폰시킬 것인가?
	bool ShouldChainSawSpawnForSB = false;

	// ---------- -------------------- ----------

public:
	ALB_GM();

	UFUNCTION(BlueprintCallable)
	void UpdateSet();

protected:
	virtual void BeginPlay() override;

	// ---------- 플레이어 게임 오버 ----------
public:
	// 플레이어 사망 로직 (TargetLocation : 바라볼 액터의 위치, Num : 사망 종류)
	// 0 : 전기톱
	// 1 : 노커
	// 2 : 끾끾끾
	// 3: 곰탬미
	// 4: 의사
	// 10 : 낮에 시간초과
	// 11 : 밤에 시간초과
	UFUNCTION(BlueprintCallable)
	void PlayerDeathLogic(FVector TargetLocation, int32 Num);

	// ---------- -------------------- ----------

	// ---------- 플레이어 방/복도 위치 확인 관련 함수 ----------
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsPlayerInRoom = false;

	bool bShouldMusicBoxSpawn = false;

	// 플레이어가 방에서 체류한 시간(초 단위).
	//int32 AtRoomSecond = 0;
	// 오르골이 등장하기 위해 방에 체류해야 하는 시간(초 단위).
	//int32 AtRoomSecondForMusicBox = 80;

	// 플레이어가 방에서 나갈 때 오르골이 등장하기 위해 방에 체류해야 하는 최소 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LobbyDurationForMusicBox_Min = 15;
	// 플레이어가 방에서 나갈 때 오르골이 등장하기 위해 방에 체류해야 하는 최대 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LobbyDurationForMusicBox_Max = 25;

	// 플레이어가 방에서 오래 있으면 숨바꼭질 장인이 등장하기까지 걸리는 최소 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RoomDurationForSpawnHAS_Min = 20;
	// 플레이어가 방에서 오래 있으면 숨바꼭질 장인이 등장하기까지 걸리는 최대 시간.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RoomDurationForSpawnHAS_Max = 30;

	//// 플레이어가 복도에서 오래 있으면 숨바꼭질 장인이 근처 방에서 등장하기까지 걸리는 최소 시간.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float LobbyDurationForSpawnHAS_Min = 55.0f;
	//// 플레이어가 복도에서 오래 있으면 숨바꼭질 장인이 근처 방에서 등장하기까지 걸리는 최대 시간.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float LobbyDurationForSpawnHAS_Max = 85.0f;

protected:
	FTimerHandle AtLobbyTimerHandle;
	FTimerHandle AtRoomTimerHandle;

public:
	// 후반 일차에 갈 수록 스폰에 필요한 시간을 감소시키는 로직.
	float CalculateSpawnDelay(int32 Min, int32 Max);

	// 플레이어가 복도에서 나가 방에 도달했을 때 실행됨.
	void PlayerIntoRoom();
	// 플레이어가 방에서 나가 복도에 도달했을 때 실행됨.
	void PlayerIntoLobby();

	// 플레이어가 방에 있는 경우 매 초 AtRoomSecond를 올림.
	//void AtRoomSecondTimer();

	// 플레이어가 복도/방 체류시간 초과시 다음 실행을 블루프린트로 넘겨줌.
	UFUNCTION(BlueprintImplementableEvent)
	void OnStayTimeOut();

	// 플레이어가 방에서 나갈 때 오르골 스폰해야 하는 경우 다음 실행을 블루프린트로 넘겨줌.
	UFUNCTION(BlueprintImplementableEvent)
	void OnMusicBoxSpawnTime();
	// ---------- -------------------- ----------

	// ---------- 숨바꼭질 장인 관련 함수 ----------
public:
	// 숨바꼭질 장인이 노크한 횟수 증가
	void AddKnockCount();

	// 숨바꼭질 장인이 노크한 횟수 초기화
	void ResetKnockCount();

	// 숨바꼭질 장인이 인사한 횟수 증가
	void AddHelloCount();

	// 숨바꼭질 장인이 인사한 횟수 초기화
	void ResetHelloCount();

	// 숨바꼭질 장인 스폰 여부 설정
	FORCEINLINE void SetIsHidAndSeekerSpawned(bool Value) { bIsHidAndSeekerSpawned = Value; }

	// 숨바꼭질 장인이 스폰되어 있는가?
	FORCEINLINE bool GetIsHidAndSeekerSpawned() const { return bIsHidAndSeekerSpawned; }
	// ---------- -------------------- ----------
	
	// ---------- 전기톱 살인마 관련 함수 ----------
public:
	UFUNCTION(BlueprintCallable)
	void SafeBoxAlertCountUp();

	UFUNCTION(BlueprintCallable)
	void SafeBoxAlertCountReset();

	// 전기톱 살인마 스폰 여부 설정
	FORCEINLINE void SetIsChainSawManSpawned(bool Value) { bIsChainSawManSpawned = Value; }

	// 전기톱 살인마 레퍼런스 등록
	void SetChainSawManRef(ALB_Monster_ChainSawMan* CSM);

	// 전기톱 살인마 위치 재설정
	UFUNCTION(BlueprintCallable)
	void SetChainSawManTransform(FTransform NewTransform);

	// 잔여 몹 제거
	UFUNCTION(BlueprintCallable)
	void AllMonsterDestroy();
	

	// 전기톱 살인마가 노커 때문에 개빡친 상황인가?
	//FORCEINLINE bool GetShouldChainSawManSpawn() const { return ShouldChainSawManSpawn; }

	// 노커가 문을 열 차례인가?
	FORCEINLINE bool GetShouldOpenDoor() const { return ShouldOpenDoor; }

	// 노커가 개빡친 상황인가?
	FORCEINLINE bool GetShouldHASAttackMode() const { return ShouldHASAttackMode; }

	// 전기톱 살인마가 스폰되어 있는가?
	UFUNCTION(BlueprintPure)
	bool GetIsChainSawManSpawned() const { return bIsChainSawManSpawned; }

	// 금고때문에 전기톱 살인마가 개빡친 상황인가?
	UFUNCTION(BlueprintPure)
	bool GetShouldChainSawSpawnForSB();

	// 전기톱 살인마가 플레이어와 내비메시 길찾기 경로상 얼만큼 떨어져 있는가?
	UFUNCTION(BlueprintPure)
	float GetChainSawManToPlayerDistance();
	// ---------- -------------------- ----------

	// ---------- 곰탱이 관련 함수 ----------
public:
	// 곰탱이 괴물 레퍼런스 등록
	void SetTeddyBearRef(ALB_Monster_TeddyBear* TB);

	// 곰탱이 인형 레퍼런스 등록
	void SetTeddyRef(ALB_TeddyBear* TB);

	// 곰탱이 괴물 레퍼런스 가져오기
	FORCEINLINE ALB_Monster_TeddyBear* GetTeddyBearRef() const { return TeddyBearRef; }

	// 곰탱이 인형 레퍼런스 가져오기
	FORCEINLINE ALB_TeddyBear* GetTeddyRef() const { return TeddyRef; }

	// ---------- -------------------- ----------

	// ---------- 마네킹 관련 함수 ----------
public:
	// 마네킹 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ManequinClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	bool ManequinSpawnDay = false;

	// 마네킹 레퍼런스 등록
	void SetManequinRef(ALB_Monster_Manequin* MQ);

	// 마네킹 스폰
	void SpawnManequin();

	// 마네킹 디스폰
	void DespawnManequin();

	// ---------- -------------------- ----------


	// ------------- 날짜 & 밤낮 ---------
public:
	// 현재 날짜 (1일부터 시작)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Days")
	int32 CurrentDay = 1;

	// 낮/밤 여부 (true = 밤, false = 낮)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Days")
	bool bIsNight = false;

	UFUNCTION(BlueprintCallable)
	void UpdateDate();

	// 날짜 초기화 (1일로)
	UFUNCTION(BlueprintCallable)
	void ClearDate();

	// 낮 → 밤
	UFUNCTION(BlueprintCallable)
	void ChangeToNight();

	// 밤 → 낮
	UFUNCTION(BlueprintCallable)
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
//------------- 차트 시스템 ---------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chart")
	UDataTable* ChartDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	int32 CurrentPage = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	FChartData CurrentChart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	TMap<int32, FChartData> RuntimeCharts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chart")
	TArray<FName> NameOfPatients;

	UFUNCTION(BlueprintCallable, Category = "Chart")
	void LoadPage(int32 NewPage);

	UFUNCTION(BlueprintCallable, Category = "Chart")
	FChartData GetChartCopy(int32 Page) const;

	UFUNCTION(BlueprintCallable, Category = "Chart")
	FChartData GetCurrentChartCopy() const { return CurrentChart; }

	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetNameForPage(int32 Page, const FText& NewName);
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetSymptomForPage(int32 Page, const FText& NewSymptom);
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetRemarkForPage(int32 Page, const FText& NewRemark);
	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetRoomNumberForPage(int32 Page, const FText& NewRemark);

	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetDayCheckForPage(int32 Page, int32 DayIndex /*0~6*/, bool bChecked);

	UFUNCTION(BlueprintCallable, Category = "Chart")
	void SetNightCheckForPage(int32 Page, int32 DayIndex /*0~6*/, bool bChecked);

	UPROPERTY(BlueprintAssignable, Category = "Chart")
	FOnChartUpdated OnChartUpdated;

private:
	bool EnsurePageInCache(int32 Page);

	void SyncCurrentFromCacheAndBroadcast();

	//--------------대화 UI-------------
	public:
		UFUNCTION(BlueprintCallable)
		void StartDialogue(FName StartRow);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULB_DialogueUI> DialogueWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UDataTable* DialogueTable;

	// ---------- 설정 관련 함수 ----------
public:
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveOtherSetting(int32 MasterVolume);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadOtherSetting(int32& MasterVolume);
	// ---------- -------------------- ----------
};
