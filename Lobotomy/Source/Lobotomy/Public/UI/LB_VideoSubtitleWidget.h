#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/LB_SubtitleData.h"
#include "LB_VideoSubtitleWidget.generated.h"

UCLASS()
class LOBOTOMY_API ULB_VideoSubtitleWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
    class UMediaPlayer* MediaPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
    class UMediaSource* MediaSource;

    UPROPERTY(meta = (BindWidget))
    UImage* VideoImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
    class UMediaTexture* MediaTexture;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SubtitleText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
    UDataTable* SubtitleTable_KR;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
    UDataTable* SubtitleTable_EN;

    UPROPERTY()
    UDataTable* ActiveSubtitleTable;

private:
    UPROPERTY()
    TArray<FLB_SubtitleData> Subtitles;

    int32 CurrentIndex = -1;

    UPROPERTY()
    class UMediaSoundComponent* MediaSoundComp;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsStoped = false;

private:
    void LoadSubtitleTable();
    void SetupMediaSound();

public:
    UFUNCTION(BlueprintCallable)
    void PlayVideo();

    UFUNCTION(BlueprintCallable)
    void PauseVideo();

    UFUNCTION(BlueprintCallable)
    void StopVideo();

	UFUNCTION(BlueprintImplementableEvent)
	void OnVideoStarted();
};
