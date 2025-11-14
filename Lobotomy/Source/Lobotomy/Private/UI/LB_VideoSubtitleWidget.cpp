#include "UI/LB_VideoSubtitleWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "MediaSoundComponent.h"
#include "Components/AudioComponent.h"

void ULB_VideoSubtitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // if (MediaPlayer)
    // {
    //     UWorld* World = GetWorld();
    //     if (World)
    //     {
    //         UMediaSoundComponent* MediaSound = NewObject<UMediaSoundComponent>(World->GetWorldSettings());
    //         if (MediaSound)
    //         {
    //             MediaSound->SetMediaPlayer(MediaPlayer);
    //             MediaSound->RegisterComponent();
    //             MediaSound->Activate(true);
    //         }
    //     }
    // }

    LoadSRTFile();

    if (MediaPlayer && MediaSource)
    {
        MediaPlayer->OpenSource(MediaSource);
        MediaPlayer->Play();
    }
}

void ULB_VideoSubtitleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

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
                SubtitleText->SetText(FText::FromString(Subtitles[i].Text));
            }
            return;
        }
    }

    if (CurrentIndex != -1)
    {
        CurrentIndex = -1;
        SubtitleText->SetText(FText::GetEmpty());
    }
}

void ULB_VideoSubtitleWidget::LoadSRTFile()
{
    FString FullPath = FPaths::ProjectContentDir() / SubtitleFilePath;
    TArray<FString> Lines;

    if (!FFileHelper::LoadFileToStringArray(Lines, *FullPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("자막 로드 실패: %s"), *FullPath);
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

}

void ULB_VideoSubtitleWidget::ChangeSubtitleFile(const FString& NewSubtitlePath)
{
    SubtitleFilePath = NewSubtitlePath;
    LoadSRTFile();

    CurrentIndex = -1;
    SubtitleText->SetText(FText::GetEmpty());

    UE_LOG(LogTemp, Log, TEXT("Subtitle file changed to: %s"), *SubtitleFilePath);
}
