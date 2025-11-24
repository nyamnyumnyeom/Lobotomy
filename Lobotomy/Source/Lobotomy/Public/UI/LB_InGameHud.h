#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "LB_ItemData.h"
#include "LB_GM.h"
#include "Character/LB_Character.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "LB_InGameHud.generated.h"

class UImage;
class UInventoryComponent;

UCLASS()
class LOBOTOMY_API ULB_InGameHud : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateBattery(float BatteryLevel);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UpdateInventory();

    UPROPERTY(meta = (BindWidget))
    UProgressBar* StaminaBar;

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void UpdateStamina(float CurrentStamina);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundBase* LowStaminaSound;

    bool bIsLowStaminaSoundPlayed = false;
    float StaminaBlinkTimer = 0.0f;


protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery01;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery02;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery03;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery04;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery05;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UTextBlock* ItemNameText;

    UPROPERTY(meta = (BindWidget)) UImage* InvItem;

    // DataTable을 에디터에서 연결할 수 있게 프로퍼티로 추가
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    UDataTable* ItemDataTable;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* GameTimeText;

    void UpdateGameTime();

private:
    ALB_Character* PlayerCharacter;

    TWeakObjectPtr<ALB_GM> GameModeRef;
};
