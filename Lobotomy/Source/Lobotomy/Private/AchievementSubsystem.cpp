#include "AchievementSubsystem.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "OnlineSubsystemTypes.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "steam/steam_api.h"
#pragma warning(pop)

void UAchievementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] OnlineSubsystem initialized: %s"),
			*OSS->GetSubsystemName().ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[AchievementSubsystem] OnlineSubsystem is invalid. Check configuration."));
	}
}

void UAchievementSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAchievementSubsystem::UnlockAchievement(FName AchievementID)
{
	FString AchievementString = AchievementID.ToString();

	// 1. SteamAPI 초기화 확인
	if (!SteamAPI_Init())
	{
		UE_LOG(LogTemp, Warning, TEXT("[AchievementSubsystem] SteamAPI is not initialized!"));
		return;
	}

	if (!SteamUserStats())
	{
		UE_LOG(LogTemp, Warning, TEXT("[AchievementSubsystem] SteamUserStats() is null!"));
		return;
	}

	// 2. 테스트 편의를 위해 매번 실행할 때마다 기존 업적을 잠금(초기화)합니다.
	// (실서비스 출시 시점에는 이 줄을 주석 처리하거나 제거하셔야 유저의 업적이 매번 초기화되지 않습니다.)
	SteamUserStats()->ClearAchievement(TCHAR_TO_ANSI(*AchievementString));
	SteamUserStats()->StoreStats();
	UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] Cleared achievement for testing: %s"), *AchievementString);

	// 3. 현재 스팀 유저의 통계/업적 데이터 요청
	if (!SteamUserStats()->RequestCurrentStats())
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] RequestCurrentStats failed!"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] RequestCurrentStats success!"));

	// 4. 업적의 현재 달성 상태 확인
	bool bIsAchieved = false;
	if (!SteamUserStats()->GetAchievement(TCHAR_TO_ANSI(*AchievementString), &bIsAchieved))
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] GetAchievement failed for: %s"), *AchievementString);
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] Achievement %s current state: %s"), *AchievementString, bIsAchieved ? TEXT("Unlocked") : TEXT("Locked"));

	// 이미 달성한 도전과제라면 리턴
	if (bIsAchieved)
	{
		return;
	}

	// 5. 도전과제 달성 설정
	if (!SteamUserStats()->SetAchievement(TCHAR_TO_ANSI(*AchievementString)))
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] SetAchievement failed!"));
		return;
	}

	// 6. 변경된 데이터 스팀 서버로 전송 및 저장
	if (!SteamUserStats()->StoreStats())
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] StoreStats failed!"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] Successfully unlocked and stored achievement: %s"), *AchievementString);
}

void UAchievementSubsystem::SetSteamStat(FName StatID, int32 Value)
{
	FString StatString = StatID.ToString();

	// 1. SteamAPI 초기화 확인
	if (!SteamAPI_Init() || !SteamUserStats())
	{
		UE_LOG(LogTemp, Warning, TEXT("[AchievementSubsystem] SteamAPI or SteamUserStats is invalid!"));
		return;
	}

	// 2. 현재 통계 데이터 요청 (최신 상태 보장)
	if (!SteamUserStats()->RequestCurrentStats())
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] RequestCurrentStats failed for Stat!"));
		return;
	}

	// 3. 스팀 서버에 Stat 값 설정
	if (!SteamUserStats()->SetStat(TCHAR_TO_ANSI(*StatString), Value))
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] SetStat failed for: %s"), *StatString);
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] SetStat success: %s = %d"), *StatString, Value);

	// 4. 변경된 통계를 스팀 서버로 전송 및 저장 (이때 조건이 충족되면 업적이 자동 해제됩니다)
	if (!SteamUserStats()->StoreStats())
	{
		UE_LOG(LogTemp, Error, TEXT("[AchievementSubsystem] StoreStats failed for Stat!"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[AchievementSubsystem] Successfully stored stat: %s"), *StatString);
}