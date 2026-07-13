#include "AchievementSubsystem.h"


// #include "OnlineSubsystem.h"
// #include "Interfaces/OnlineAchievementsInterface.h"
// #include "Interfaces/OnlineIdentityInterface.h"
// #include "OnlineSubsystemUtils.h"
// #include "OnlineSubsystemTypes.h"

void UAchievementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    /*
     // -------------------------------------------------------------------------
     // OnlineSubsystem 초기화
     // -------------------------------------------------------------------------

     IOnlineSubsystem* OSS = IOnlineSubsystem::Get();

     if (OSS)
     {
         UE_LOG(LogAchievement, Log, TEXT("OnlineSubsystem : %s"),
             *OSS->GetSubsystemName().ToString());
     }
     else
     {
         UE_LOG(LogAchievement, Error, TEXT("OnlineSubsystem Invalid"));
     }
     */

    // TODO : OnlineSubsystem 초기화
}

void UAchievementSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UAchievementSubsystem::UnlockAchievement(FName AchievementID)
{
    const FString AchievementString = AchievementID.ToString();

    UE_LOG(LogTemp, Log,
        TEXT("[Achievement] Unlock Requested : %s"),
        *AchievementString);

    // TODO : OnlineSubsystemSteam Achievement 연동
    /*
    Steam 업적 해금 (AppID 발급 후 활성화)
 /*
    // -------------------------------------------------------------------------
    // Steam Achievement (OnlineSubsystem)
    // -------------------------------------------------------------------------

    // OnlineSubsystem 가져오기
    IOnlineSubsystem* OSS = IOnlineSubsystem::Get();

    if (!OSS)
    {
        UE_LOG(LogAchievement, Error, TEXT("OnlineSubsystem Invalid"));
        return;
    }

    // Achievement Interface
    IOnlineAchievementsPtr AchievementInterface =
        OSS->GetAchievementsInterface();

    if (!AchievementInterface.IsValid())
    {
        UE_LOG(LogAchievement, Error,
            TEXT("Achievement Interface Invalid"));
        return;
    }

    // Local Player
    ULocalPlayer* LocalPlayer =
        GetGameInstance()->GetFirstGamePlayer();

    if (!LocalPlayer)
    {
        UE_LOG(LogAchievement, Error,
            TEXT("LocalPlayer Invalid"));
        return;
    }

    // Unique Net ID
    FUniqueNetIdPtr UserId =
        LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId();

    if (!UserId.IsValid())
    {
        UE_LOG(LogAchievement, Error,
            TEXT("UniqueNetId Invalid"));
        return;
    }

    // Achievement Write
    FOnlineAchievementsWritePtr WriteObject =
        MakeShared<FOnlineAchievementsWrite>();

    WriteObject->SetFloatStat(
        AchievementID.ToString(),
        100.0f);

    // Delegate
    FOnAchievementsWrittenDelegate Delegate =
        FOnAchievementsWrittenDelegate::CreateLambda(
        [](const FUniqueNetId& PlayerId, bool bSuccess)
        {
            UE_LOG(LogAchievement, Log,
                TEXT("Achievement Write Result : %s"),
                bSuccess ? TEXT("Success") : TEXT("Failed"));
        });

    // Write
    AchievementInterface->WriteAchievements(
        *UserId,
        WriteObject.ToSharedRef(),
        Delegate);

    */
    */
}