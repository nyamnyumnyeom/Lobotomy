#include "MiniGame/LB_Obstaclewidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "MiniGame/LB_ObstaclePush.h"

void ULB_Obstaclewidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (TargetActor == nullptr || TimeText == nullptr)
        return;

    float Remaining = TargetActor->GetRemainingTime();

    int32 Seconds = FMath::FloorToInt(Remaining);
    TimeText->SetText(FText::AsNumber(Seconds));

    if (Remaining <= 5.f)
    {
        FlashTimer += InDeltaTime * 6.f;
        float Alpha = (FMath::Sin(FlashTimer) + 1.f) * 0.5f;

        TimeText->SetColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, Alpha));
    }
    else
    {
        TimeText->SetColorAndOpacity(FLinearColor::White);
        FlashTimer = 0.f;
    }

    if (HoverBar && TargetActor->TimeRequired > 0.f)
    {
        float Percent = TargetActor->HoveredTime / TargetActor->TimeRequired;
        Percent = FMath::Clamp(Percent, 0.f, 1.f);

        HoverBar->SetPercent(Percent);
    }
}

void ULB_Obstaclewidget::SetTargetActor(ALB_ObstaclePush* NewTarget)
{
    TargetActor = NewTarget;
}