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
    //UE_LOG(LogTemp, Warning, TEXT("[HUD] UpdateInventory called."));

    if (!InvItem)
    {
        //UE_LOG(LogTemp, Error, TEXT("[HUD] InvItem is NULL! (BindWidget 누락됨)"));
        return;
    }

    if (!PlayerCharacter)
    {
        //UE_LOG(LogTemp, Error, TEXT("[HUD] PlayerCharacter is NULL! (NativeConstruct에서 캐릭터 캐스팅 실패)"));
        return;
    }

    if (!ItemDataTable)
    {
        //UE_LOG(LogTemp, Error, TEXT("[HUD] ItemDataTable is NULL! (WBP_InGameHud에서 연결 안됨)"));
        return;
    }

    FName CurrentItemCode = PlayerCharacter->CurrentItem;
    //UE_LOG(LogTemp, Warning, TEXT("[HUD] CurrentItemCode = %s"), *CurrentItemCode.ToString());

    if (CurrentItemCode == NAME_None)
    {
        //UE_LOG(LogTemp, Warning, TEXT("[HUD] No current item -> hiding inventory icon."));
        InvItem->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    static const FString Context(TEXT("FindItemRow"));
    FItemRow* FoundRow = ItemDataTable->FindRow<FItemRow>(CurrentItemCode, Context);

    if (!FoundRow)
    {
        //UE_LOG(LogTemp, Error, TEXT("[HUD] Could not find row in DataTable for item: %s"), *CurrentItemCode.ToString());
        InvItem->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    if (!FoundRow->ItemIcon)
    {
        //UE_LOG(LogTemp, Error, TEXT("[HUD] Found row but ItemIcon is NULL: %s"), *CurrentItemCode.ToString());
        InvItem->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    // 성공 시
    //UE_LOG(LogTemp, Warning, TEXT("[HUD] Found item icon successfully! Updating HUD with icon from: %s"), *CurrentItemCode.ToString());

    InvItem->SetBrushFromTexture(FoundRow->ItemIcon);
    InvItem->SetVisibility(ESlateVisibility::Visible);
}


void ULB_InGameHud::UpdateGameTime()
{
    if (!GameTimeText || !GameModeRef.IsValid()) return;

    int32 Hours, Minutes;
    GameModeRef->GetGameTime(Hours, Minutes);

    FString TimeString = FString::Printf(TEXT("%02d : %02d"), Hours, Minutes);
    GameTimeText->SetText(FText::FromString(TimeString));
}