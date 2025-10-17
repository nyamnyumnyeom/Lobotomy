#include "UI/LB_InGameHud.h"
#include "Kismet/GameplayStatics.h"
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

//void ULB_InGameHud::UpdateInventory()
//{
//    if (!InvItem || !PlayerCharacter || !PlayerCharacter->InventoryComponent)
//        return;
//
//    // 예시: 인벤토리 안에 아이템 이름으로 매칭하는 방식
//    const TArray<FString> Items = PlayerCharacter->InventoryComponent->GetItemNames();
//
//    // 예: a 아이템이 있으면 a1.png 표시, b 아이템이 있으면 b2.png 표시
//    FString TextureName = TEXT("Default");
//    if (Items.Contains("a"))
//        TextureName = TEXT("a1");
//    else if (Items.Contains("b"))
//        TextureName = TEXT("b2");
//    else if (Items.Contains("c"))
//        TextureName = TEXT("c3");
//
//    FString Path = FString::Printf(TEXT("/Game/UI/Textures/%s.%s"), *TextureName, *TextureName);
//    UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *Path));
//
//    if (Texture)
//    {
//        InvItem->SetBrushFromTexture(Texture);
//        InvItem->SetVisibility(ESlateVisibility::Visible);
//    }
//    else
//    {
//        InvItem->SetVisibility(ESlateVisibility::Hidden);
//    }
//}