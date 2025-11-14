#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"

#include "LB_SettingUI.generated.h"


UCLASS()
class LOBOTOMY_API ULB_SettingUI : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void SynchronizeProperties() override;

    UPROPERTY(meta = (BindWidget)) USlider* SliderVolume;
    UPROPERTY(meta = (BindWidget)) USlider* SliderSensitivity;
    UPROPERTY(meta = (BindWidget)) USlider* SliderBrightness;

    UPROPERTY(meta = (BindWidget)) UComboBoxString* ComboResolution;
    UPROPERTY(meta = (BindWidget)) UComboBoxString* ComboWindowMode;
    UPROPERTY(meta = (BindWidget)) UComboBoxString* ComboAA;
    UPROPERTY(meta = (BindWidget)) UComboBoxString* ComboPost;
    UPROPERTY(meta = (BindWidget)) UComboBoxString* ComboShadow;
    UPROPERTY(meta = (BindWidget)) UComboBoxString* ComboTexture;

    UPROPERTY(meta = (BindWidget)) UButton* ButtonApply;
    UPROPERTY(meta = (BindWidget)) UButton* ButtonReset;

private:
    UFUNCTION() void OnVolumeChanged(float Value);
    UFUNCTION() void OnSensitivityChanged(float Value);
    UFUNCTION() void OnBrightnessChanged(float Value);

    UFUNCTION() void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type Type);
    UFUNCTION() void OnWindowModeChanged(FString SelectedItem, ESelectInfo::Type Type);
    UFUNCTION() void OnAAChanged(FString SelectedItem, ESelectInfo::Type Type);
    UFUNCTION() void OnPostChanged(FString SelectedItem, ESelectInfo::Type Type);
    UFUNCTION() void OnShadowChanged(FString SelectedItem, ESelectInfo::Type Type);
    UFUNCTION() void OnTextureChanged(FString SelectedItem, ESelectInfo::Type Type);

    UFUNCTION() void OnApplyClicked();
    UFUNCTION() void OnResetClicked();

    int32 ParseQuality(const FString& Item) const;
};