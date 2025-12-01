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
        UpdateStamina(PlayerCharacter->Stamina);
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
        UpdateStamina(PlayerCharacter->Stamina);
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

void ULB_InGameHud::UpdateStamina(float CurrentStamina)
{
    if (!StaminaBar || !PlayerCharacter) return;

    float MaxStamina = PlayerCharacter->MaxStamina;
    float Percent = CurrentStamina / MaxStamina;
    StaminaBar->SetPercent(Percent);

    if (Percent < 0.1f)
    {
        StaminaBlinkTimer += GetWorld()->GetDeltaSeconds();
        float BlinkAlpha = (FMath::Sin(StaminaBlinkTimer * 12.0f) + 1.0f) * 0.5f;

        FLinearColor RedColor = FLinearColor(1.f, 0.f, 0.f, BlinkAlpha);
        StaminaBar->SetFillColorAndOpacity(RedColor);

        if (!bIsLowStaminaSoundPlayed && LowStaminaSound)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), LowStaminaSound);
            bIsLowStaminaSoundPlayed = true;
        }
    }
    else if (Percent < 0.3f)
    {
        StaminaBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.4f, 0.f, 1.f));
        StaminaBlinkTimer = 0.0f;
    }
    else if (Percent < 0.5f)
    {
        StaminaBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f, 1.f));
        StaminaBlinkTimer = 0.0f;
    }
    else
    {
        StaminaBar->SetFillColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
        StaminaBlinkTimer = 0.0f;
    }

    if (Percent > 0.1f)
    {
        bIsLowStaminaSoundPlayed = false;
    }
}
