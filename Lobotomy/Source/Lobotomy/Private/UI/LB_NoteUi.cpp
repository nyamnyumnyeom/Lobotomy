#include "UI/LB_NoteUi.h"
#include "Kismet/GameplayStatics.h"
#include "LB_GM.h"

void ULB_NoteUi::NativeConstruct()
{
    Super::NativeConstruct();

    if (NameText) NameText->SetText(FText::FromString(TEXT("Name")));
    if (SymptomText) SymptomText->SetText(FText::FromString(TEXT("Symptom")));
    if (RemarkText) RemarkText->SetText(FText::FromString(TEXT("Remark")));
    if (PageNumberText) PageNumberText->SetText(FText::FromString(TEXT("Page 1")));

    if (ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(this)))
    {
        RefreshFromGameMode();

        GM->OnChartUpdated.AddDynamic(this, &ULB_NoteUi::HandleChartUpdated);
    }
}
void ULB_NoteUi::HandleChartUpdated(int32 /*PageNumber*/)
{
    // 필요시 PageNumber 활용 가능
    RefreshFromGameMode();
}


void ULB_NoteUi::SetName(const FText& NewName)
{
    if (NameText)
        NameText->SetText(NewName);
}

void ULB_NoteUi::SetSymptom(const FText& NewSymptom)
{
    if (SymptomText)
        SymptomText->SetText(NewSymptom);
}

void ULB_NoteUi::SetRemark(const FText& NewRemark)
{
    if (RemarkText)
        RemarkText->SetText(NewRemark);
}

void ULB_NoteUi::SetPageNumber(int32 PageNumber)
{
    if (PageNumberText)
        PageNumberText->SetText(FText::FromString(FString::Printf(TEXT("Page %d"), PageNumber)));
}

void ULB_NoteUi::SetDayChecked(int32 DayIndex, bool bChecked)
{
    TArray<UCheckBox*> Days = { Day01, Day02, Day03, Day04, Day05, Day06, Day07 };

    if (Days.IsValidIndex(DayIndex))
    {
        if (Days[DayIndex])
        {
            Days[DayIndex]->SetIsChecked(bChecked);
        }
    }
}

void ULB_NoteUi::RefreshFromGameMode()
{
    if (ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(this)))
    {
        const FChartData Data = GM->GetCurrentChartCopy();

        if (NameText)       NameText->SetText(Data.Name);
        if (SymptomText)    SymptomText->SetText(Data.Symptom);
        if (RemarkText)     RemarkText->SetText(Data.Remark);
        if (PageNumberText) PageNumberText->SetText(FText::AsNumber(Data.PageNumber));

        // 체크박스들 반영 (0~6)
        auto GetDay = [&](int32 I)->bool { return Data.DayChecks.IsValidIndex(I) ? Data.DayChecks[I] : false; };
        if (Day01) Day01->SetIsChecked(GetDay(0));
        if (Day02) Day02->SetIsChecked(GetDay(1));
        if (Day03) Day03->SetIsChecked(GetDay(2));
        if (Day04) Day04->SetIsChecked(GetDay(3));
        if (Day05) Day05->SetIsChecked(GetDay(4));
        if (Day06) Day06->SetIsChecked(GetDay(5));
        if (Day07) Day07->SetIsChecked(GetDay(6));

		// 체크박스들 반영 (0~6)
		auto GetNight = [&](int32 I)->bool { return Data.NightChecks.IsValidIndex(I) ? Data.NightChecks[I] : false; };
		if (Night01) Night01->SetIsChecked(GetNight(0));
		if (Night02) Night02->SetIsChecked(GetNight(1));
		if (Night03) Night03->SetIsChecked(GetNight(2));
		if (Night04) Night04->SetIsChecked(GetNight(3));
		if (Night05) Night05->SetIsChecked(GetNight(4));
		if (Night06) Night06->SetIsChecked(GetNight(5));
		if (Night07) Night07->SetIsChecked(GetNight(6));
    }
}