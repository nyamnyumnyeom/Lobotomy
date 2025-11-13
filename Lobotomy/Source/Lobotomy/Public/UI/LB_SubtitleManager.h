#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MediaPlayer.h"
#include "LB_SubtitleData.h"
#include "LB_SubtitleManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubtitleChanged, const FString&, SubtitleText);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API ULB_SubtitleManager : public UActorComponent
{
    GENERATED_BODY()

public:
    ULB_SubtitleManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitle")
    UMediaPlayer* MediaPlayer;

    UPROPERTY(BlueprintAssignable, Category = "Subtitle")
    FOnSubtitleChanged OnSubtitleChanged;

    UFUNCTION(BlueprintCallable)
    void LoadSRTFile(const FString& FilePath);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    TArray<FLB_SubtitleData> Subtitles;
    int32 CurrentIndex = -1;
};
