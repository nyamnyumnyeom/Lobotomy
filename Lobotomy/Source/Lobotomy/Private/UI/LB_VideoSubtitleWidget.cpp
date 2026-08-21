#include "UI/LB_VideoSubtitleWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "MediaSoundComponent.h"
#include "Internationalization/Culture.h"
#include "Internationalization/Internationalization.h"
#include "Components/AudioComponent.h"

void ULB_VideoSubtitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 현재 언어 구하기
    FString Lang = FInternationalization::Get().GetCurrentCulture()->GetName();

    // 언어에 맞는 테이블 선택
    if (Lang.StartsWith("ko"))
    {
        ActiveSubtitleTable = SubtitleTable_KR;
    }
    else if (Lang.StartsWith("en"))
    {
        ActiveSubtitleTable = SubtitleTable_EN;
    }
    else
    {
        ActiveSubtitleTable = SubtitleTable_EN;
    }

    SubtitleText->SetText(FText::GetEmpty());

    if (MediaTexture && VideoImage && MediaPlayer)
    {
        MediaTexture->SetMediaPlayer(MediaPlayer);

        FIntPoint Size = MediaPlayer->GetVideoTrackDimensions(0, 0);
        FVector2D FinalSize(Size.X, Size.Y);

        FSlateBrush Brush;
        Brush.SetResourceObject(MediaTexture);

        if (FinalSize.X <= 0 || FinalSize.Y <= 0)
        {
            FinalSize = FVector2D(1920, 1080);
        }

        Brush.ImageSize = FinalSize;

        VideoImage->SetBrush(Brush);
    }


    LoadSubtitleTable();
    SetupMediaSound();

    PlayVideo();
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
        if (CurrentTime >= Subtitles[i].StartTime &&
            CurrentTime <= Subtitles[i].EndTime)
        {
            CurrentIndex = i;
            SubtitleText->SetText(Subtitles[i].Subtitle);
            return;
        }
    }

    if (CurrentIndex != -1)
    {
        CurrentIndex = -1;
        SubtitleText->SetText(FText::GetEmpty());
    }
}

void ULB_VideoSubtitleWidget::SetupMediaSound()
{
    if (!MediaPlayer) return;

    UWorld* World = GetWorld();
    if (!World) return;

    MediaSoundComp = NewObject<UMediaSoundComponent>(World->GetWorldSettings());

    if (MediaSoundComp)
    {
        MediaSoundComp->SetMediaPlayer(MediaPlayer);
        MediaSoundComp->RegisterComponent();
        MediaSoundComp->Activate(true);
    }
}

void ULB_VideoSubtitleWidget::LoadSubtitleTable()
{
    Subtitles.Empty();
    CurrentIndex = -1;

    if (!ActiveSubtitleTable) return;

    TArray<FName> RowNames = ActiveSubtitleTable->GetRowNames();

    for (auto& RowName : RowNames)
    {
        FLB_SubtitleData* Row = ActiveSubtitleTable->FindRow<FLB_SubtitleData>(RowName, TEXT("SubLoad"));
        if (Row)
        {
            FLB_SubtitleData Data;
            Data.StartTime = Row->StartTime;
            Data.EndTime = Row->EndTime;
            Data.Subtitle = Row->Subtitle;

            Subtitles.Add(Data);
        }
    }

    Subtitles.Sort([](const FLB_SubtitleData& A, const FLB_SubtitleData& B)
        {
            return A.StartTime < B.StartTime;
        });
}



void ULB_VideoSubtitleWidget::PlayVideo()
{
    if (!MediaPlayer || !MediaSource) return;

    if (!MediaPlayer->IsReady())
    {
        MediaPlayer->OpenSource(MediaSource);
    }

    MediaPlayer->Play();

    if (MediaSoundComp)
    {
        MediaSoundComp->Activate(true);
    }

	OnVideoStarted();
}


void ULB_VideoSubtitleWidget::PauseVideo()
{
    if (!MediaPlayer) return;

    MediaPlayer->Pause();

    if (MediaSoundComp)
    {
        MediaSoundComp->Deactivate();
    }
}

void ULB_VideoSubtitleWidget::StopVideo()
{
	bIsStoped = true;

    if (!MediaPlayer) return;

    MediaPlayer->Close();
    CurrentIndex = -1;

    if (SubtitleText)
        SubtitleText->SetText(FText::GetEmpty());

    if (MediaSoundComp)
        MediaSoundComp->Deactivate();
}

