#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "LB_Obstaclewidget.generated.h"

class UTextBlock;
class ALB_ObstaclePush;
class UImage;
class UCanvasPanelSlot;

UCLASS()
class LOBOTOMY_API ULB_Obstaclewidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* HoverBar;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TimeText;

    UPROPERTY(BlueprintReadWrite, Category = "MiniGame")
    ALB_ObstaclePush* TargetActor;

    UFUNCTION(BlueprintCallable)
    void SetTargetActor(ALB_ObstaclePush* NewTarget);

protected:
    float FlashTimer = 0.f;
};
