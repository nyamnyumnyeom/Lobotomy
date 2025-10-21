#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "LB_ItemData.h"
#include "LB_InGameHud.generated.h"

class UImage;
class ALB_Character;
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

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery01;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery02;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery03;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery04;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery05;

    UPROPERTY(meta = (BindWidget)) UImage* InvItem;

    // DataTable을 에디터에서 연결할 수 있게 프로퍼티로 추가
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    UDataTable* ItemDataTable;

private:
    ALB_Character* PlayerCharacter;
};
