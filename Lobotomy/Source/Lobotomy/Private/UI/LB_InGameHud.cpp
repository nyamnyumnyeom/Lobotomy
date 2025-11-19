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
        PlayerCharacter->OnInventoryUpdated(PlayerCharacter->CurrentItem);
        UpdateInventory();
    }

    ALB_GM* GM = Cast<ALB_GM>(GetWorld() ? GetWorld()->GetAuthGameMode() : nullptr);
    if (GM)
    {
        GameModeRef = GM;
    }

    UpdateGameTime();
}

void ULB_InGameHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (PlayerCharacter)
    {
        UpdateBattery(PlayerCharacter->BatteryLevel);
        UpdateGameTime();
        UpdateInventory();
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
    if (!InvItem || !ItemNameText) return;
    if (!PlayerCharacter) return;
    if (!ItemDataTable) return;

    FName CurrentItemCode = PlayerCharacter->CurrentItem;

    if (CurrentItemCode == NAME_None)
    {
        InvItem->SetVisibility(ESlateVisibility::Hidden);
        ItemNameText->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    static const FString Context(TEXT("FindItemRow"));
    FItemRow* FoundRow = ItemDataTable->FindRow<FItemRow>(CurrentItemCode, Context);

    if (!FoundRow || !FoundRow->ItemIcon)
    {
        InvItem->SetVisibility(ESlateVisibility::Hidden);
        ItemNameText->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    InvItem->SetBrushFromTexture(FoundRow->ItemIcon);
    InvItem->SetVisibility(ESlateVisibility::Visible);

    ItemNameText->SetText(FoundRow->ItemName);
    ItemNameText->SetVisibility(ESlateVisibility::Visible);
}


void ULB_InGameHud::UpdateGameTime()
{
    if (!GameTimeText || !GameModeRef.IsValid()) return;

    int32 Hours, Minutes;
    GameModeRef->GetGameTime(Hours, Minutes);

    FString TimeString = FString::Printf(TEXT("%02d : %02d"), Hours, Minutes);
    GameTimeText->SetText(FText::FromString(TimeString));
}