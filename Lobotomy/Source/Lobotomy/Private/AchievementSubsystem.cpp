#include "AchievementSubsystem.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"

void UAchievementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (OSS)
    {
        UE_LOG(LogTemp, Log, TEXT("OnlineSubsystem Initialized: %s"),
            *OSS->GetSubsystemName().ToString());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("OnlineSubsystem Invalid!"));
    }
}

void UAchievementSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UAchievementSubsystem::UnlockAchievement(FName AchievementID)
{
    const FString AchievementString = AchievementID.ToString();

    UE_LOG(LogTemp, Log, TEXT("[Achievement] Unlock Requested : %s"), *AchievementString);

    IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
    if (!OSS)
    {
        UE_LOG(LogTemp, Error, TEXT("Unlock Failed: OnlineSubsystem Invalid"));
        return;
    }

    IOnlineAchievementsPtr AchievementInterface = OSS->GetAchievementsInterface();
    if (!AchievementInterface.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Unlock Failed: Achievement Interface Invalid"));
        return;
    }

    ULocalPlayer* LocalPlayer = GetGameInstance() ? GetGameInstance()->GetFirstGamePlayer() : nullptr;
    if (!LocalPlayer)
    {
        UE_LOG(LogTemp, Error, TEXT("Unlock Failed: LocalPlayer Invalid"));
        return;
    }

    FUniqueNetIdPtr UserId = LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId();
    if (!UserId.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Unlock Failed: UniqueNetId Invalid (Player might not be logged into Steam)"));
        return;
    }

    FOnlineAchievementsWritePtr WriteObject = MakeShared<FOnlineAchievementsWrite>();
    WriteObject->SetFloatStat(AchievementString, 100.0f);

    FOnlineAchievementsWriteRef WriteRef = WriteObject.ToSharedRef();

    FOnAchievementsWrittenDelegate Delegate = FOnAchievementsWrittenDelegate::CreateLambda(
        [AchievementString](const FUniqueNetId& PlayerId, bool bSuccess)
        {
            if (bSuccess)
            {
                UE_LOG(LogTemp, Log, TEXT("Successfully Unlocked Achievement: %s"), *AchievementString);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to Unlock Achievement on Steam: %s"), *AchievementString);
            }
        });

    AchievementInterface->WriteAchievements(*UserId, WriteRef, Delegate);
}