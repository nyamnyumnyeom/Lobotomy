#include "LB_MiniCirgm.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULB_MiniCirgm::NativeConstruct()
{
    Super::NativeConstruct();

    if (ResultText)
        ResultText->SetVisibility(ESlateVisibility::Hidden);

    StartMiniGame();
}

void ULB_MiniCirgm::StartMiniGame()
{
    bIsPlaying = true;
    CurrentRound = 1;
    SuccessCount = 0;
    PointerAngle = 0.f;

    SpawnRandomSuccessZone();

    if (ResultText)
        ResultText->SetVisibility(ESlateVisibility::Hidden);
}

void ULB_MiniCirgm::StopMiniGame()
{
    bIsPlaying = false;
}

float ULB_MiniCirgm::NormalizeAngle(float Angle)
{
    Angle = FMath::Fmod(Angle, 360.f);
    if (Angle < 0.f)
        Angle += 360.f;

    return Angle;
}

void ULB_MiniCirgm::SpawnRandomSuccessZone()
{
    float RandomStart = FMath::FRandRange(0.f, 360.f);

    SuccessStartAngle = NormalizeAngle(RandomStart);
    SuccessEndAngle = NormalizeAngle(RandomStart + SuccessZoneSize);

    // 성공 이미지 회전
    if (SuccessZone)
    {
        FWidgetTransform Transform = SuccessZone->RenderTransform;
        Transform.Angle = SuccessStartAngle;
        SuccessZone->SetRenderTransform(Transform);
    }
}

void ULB_MiniCirgm::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!bIsPlaying)
        return;

    UpdatePointer(InDeltaTime);
}

void ULB_MiniCirgm::UpdatePointer(float DeltaTime)
{
    PointerAngle += RotateSpeed * DeltaTime;
    PointerAngle = NormalizeAngle(PointerAngle);

    if (Pointer)
    {
        FWidgetTransform Transform = Pointer->RenderTransform;
        Transform.Angle = PointerAngle;
        Pointer->SetRenderTransform(Transform);
    }
}

bool ULB_MiniCirgm::IsAngleInRange(float Angle, float Start, float End)
{
    if (Start <= End)
        return Angle >= Start && Angle <= End;

    return (Angle >= Start || Angle <= End);
}

void ULB_MiniCirgm::OnInputPressed()
{
    if (!bIsPlaying)
        return;

    Soundcall();
    CheckSuccess();
}

void ULB_MiniCirgm::CheckSuccess()
{
    bool bSuccessThisRound = IsAngleInRange(PointerAngle, SuccessStartAngle, SuccessEndAngle);

    if (bSuccessThisRound)
    {
        SuccessCount++;
        RotateSpeed += 70.f;
    }
    else
    {
        bIsPlaying = false;

        if (ResultText)
        {
            ResultText->SetVisibility(ESlateVisibility::Visible);
            ResultText->SetText(FText::FromString(TEXT("FAIL")));
        }

        OnMiniGameFail();
        return;
    }

    if (SuccessCount >= RequiredSuccessCount)
    {
        bIsPlaying = false;

        if (ResultText)
        {
            ResultText->SetVisibility(ESlateVisibility::Visible);
            ResultText->SetText(FText::FromString(TEXT("CLEAR")));
        }

        OnMiniGameCleared();
        return;
    }

    CurrentRound++;
    PointerAngle = 0.f;
    SpawnRandomSuccessZone();
}