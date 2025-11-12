#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaPlayer.h"
#include "UI/LB_SubtitleManager.h"
#include "LB_VideoSubtitleWidget.generated.h"

class UTextBlock;
class UImage;
class UMediaTexture;
class UMediaSource;

UCLASS()
class LOBOTOMY_API ULB_VideoSubtitleWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
    /** UI 요소 **/
    UPROPERTY(meta = (BindWidget))
    UTextBlock* SubtitleText;

    UPROPERTY(meta = (BindWidget))
    UImage* VideoImage;

    /** 미디어 관련 **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
    UMediaPlayer* MediaPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")
    UMediaSource* MediaSource;

    /** 자막 관련 **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
    FString SubtitleFilePath;

    UFUNCTION(BlueprintCallable, Category = "Subtitle")
    void ChangeSubtitleFile(const FString& NewSubtitlePath);


private:
    TArray<FLB_SubtitleData> Subtitles;
    int32 CurrentIndex = -1;

    void LoadSRTFile();
};