// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

    /*UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateInventory();*/

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery01;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery02;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery03;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery04;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) UImage* Battery05;

    UPROPERTY(meta = (BindWidget)) UImage* InvItem;

private:
    ALB_Character* PlayerCharacter;
};