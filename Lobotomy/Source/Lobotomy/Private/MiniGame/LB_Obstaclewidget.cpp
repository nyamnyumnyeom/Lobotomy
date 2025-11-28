#include "MiniGame/LB_Obstaclewidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "MiniGame/LB_ObstaclePush.h"

void ULB_Obstaclewidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (TargetActor == nullptr || TimeText == nullptr)
        return;

    //UpdateCursor(InDeltaTime);
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
}

void ULB_Obstaclewidget::SetTargetActor(ALB_ObstaclePush* NewTarget)
{
    TargetActor = NewTarget;
}

//void ULB_Obstaclewidget::UpdateCursor(float DeltaTime)
//{
//    if (!CursorImage) return;
//
//    FVector2D MousePos;
//    FVector2D LocalPos;
//
//    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
//    {
//        PC->GetMousePosition(MousePos.X, MousePos.Y);
//
//        LocalPos = GetCachedGeometry().AbsoluteToLocal(MousePos);
//    }
//
//    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(CursorImage->Slot))
//    {
//        CanvasSlot->SetPosition(LocalPos);
//    }
//
//
//    float Hover = TargetActor->GetHoveredTime();
//    float Req = TargetActor->TimeRequired;
//    float Ratio = FMath::Clamp(Hover / Req, 0.f, 1.f);
//
//    FLinearColor Color = FLinearColor::LerpUsingHSV(
//        FLinearColor::Green,
//        FLinearColor::Red,
//        Ratio
//    );
//    CursorImage->SetColorAndOpacity(Color);
//    float Scale = FMath::Lerp(0.6f, 1.2f, Ratio);
//    CursorImage->SetRenderScale(FVector2D(Scale, Scale));
//}