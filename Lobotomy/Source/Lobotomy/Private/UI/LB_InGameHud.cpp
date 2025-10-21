#include "UI/LB_InGameHud.h"
#include "Kismet/GameplayStatics.h"
#include "UI/LB_ItemData.h"
#include "Character/LB_Character.h"
#include "Components/Image.h"

void ULB_InGameHud::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerCharacter = Cast<ALB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (PlayerCharacter)
    {
        UpdateBattery(PlayerCharacter->BatteryLevel);
        //UpdateInventory();
    }
}

void ULB_InGameHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (PlayerCharacter)
    {
        UpdateBattery(PlayerCharacter->BatteryLevel);
        //UpdateInventory();
    }
}

void ULB_InGameHud::UpdateBattery(float BatteryLevel)
{
    if (!Battery01 || !Battery02 || !Battery03 || !Battery04 || !Battery05)
        return;

    float Percent = BatteryLevel * 100.0f;

    Battery01->SetVisibility(Percent > 0.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    Battery02->SetVisibility(Percent > 20.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    Battery03->SetVisibility(Percent > 40.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    Battery04->SetVisibility(Percent > 60.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    Battery05->SetVisibility(Percent > 80.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void ULB_InGameHud::UpdateInventory()
{
    if (!InvItem || !PlayerCharacter || !ItemDataTable)
        return;

    FName CurrentItemCode = PlayerCharacter->CurrentItem;

    if (CurrentItemCode == NAME_None)
    {
        InvItem->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    static const FString Context(TEXT("FindItemRow"));
    FItemRow* FoundRow = ItemDataTable->FindRow<FItemRow>(CurrentItemCode, Context);
    if (FoundRow && FoundRow->ItemIcon)
    {
        InvItem->SetBrushFromTexture(FoundRow->ItemIcon);
        InvItem->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        InvItem->SetVisibility(ESlateVisibility::Hidden);
    }
}