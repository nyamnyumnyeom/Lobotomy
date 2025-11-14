#include "UI/LB_SubtitleManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

ULB_SubtitleManager::ULB_SubtitleManager()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void ULB_SubtitleManager::BeginPlay()
{
    Super::BeginPlay();
}

void ULB_SubtitleManager::LoadSRTFile(const FString& FilePath)
{
    FString FullPath = FPaths::ProjectContentDir() / FilePath;
    TArray<FString> Lines;
    if (!FFileHelper::LoadFileToStringArray(Lines, *FullPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load SRT file: %s"), *FullPath);
        return;
    }

    Subtitles.Empty();
    FLB_SubtitleData Current;

    for (int32 i = 0; i < Lines.Num(); ++i)
    {
        FString Line = Lines[i].TrimStartAndEnd();
        if (Line.IsEmpty())
        {
            if (!Current.Text.IsEmpty())
            {
                Subtitles.Add(Current);
                Current = FLB_SubtitleData();
            }
            continue;
        }

        if (Line.Contains("-->"))
        {
            FString Left, Right;
            Line.Split(TEXT("-->"), &Left, &Right);

            auto ParseTime = [](const FString& TimeString)
                {
                    FString Clean = TimeString.TrimStartAndEnd().Replace(TEXT(","), TEXT("."), ESearchCase::IgnoreCase);
                    TArray<FString> Parts;
                    Clean.ParseIntoArray(Parts, TEXT(":"), true);
                    if (Parts.Num() == 3)
                    {
                        float H = FCString::Atof(*Parts[0]);
                        float M = FCString::Atof(*Parts[1]);
                        float S = FCString::Atof(*Parts[2]);
                        return H * 3600.f + M * 60.f + S;
                    }
                    return 0.f;
                };

            Current.StartTime = ParseTime(Left);
            Current.EndTime = ParseTime(Right);
        }
        else if (!Line.IsNumeric())
        {
            if (!Current.Text.IsEmpty())
                Current.Text.Append(TEXT("\n"));
            Current.Text.Append(Line);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Loaded %d subtitles."), Subtitles.Num());
}

void ULB_SubtitleManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!MediaPlayer || !MediaPlayer->IsPlaying() || Subtitles.Num() == 0)
        return;

    float CurrentTime = MediaPlayer->GetTime().GetTotalSeconds();

    if (CurrentIndex >= 0 &&
        CurrentIndex < Subtitles.Num() &&
        CurrentTime >= Subtitles[CurrentIndex].StartTime &&
        CurrentTime <= Subtitles[CurrentIndex].EndTime)
    {
        return;
    }

    for (int32 i = 0; i < Subtitles.Num(); ++i)
    {
        if (CurrentTime >= Subtitles[i].StartTime && CurrentTime <= Subtitles[i].EndTime)
        {
            if (i != CurrentIndex)
            {
                CurrentIndex = i;
                OnSubtitleChanged.Broadcast(Subtitles[i].Text);
            }
            return;
        }
    }

    if (CurrentIndex != -1)
    {
        CurrentIndex = -1;
        OnSubtitleChanged.Broadcast(TEXT(""));
    }
}
