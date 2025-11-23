#include "UI/LB_SettingUI.h"
#include "LB_Setting.h"
#include "Character/LB_PlayerController.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"

void ULB_SettingUI::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Warning, TEXT("ULB_SettingUI::NativeConstruct on!"));

    if (!ComboAA) UE_LOG(LogTemp, Error, TEXT("ComboAA is nullptr"));
    if (!ComboResolution) UE_LOG(LogTemp, Error, TEXT("ComboResolution is nullptr"));

    ULB_Setting* S = ULB_Setting::Get();
    if (!S) return;

    if (SliderVolume)      SliderVolume->SetValue(S->MasterVolume);
    if (SliderSensitivity) SliderSensitivity->SetValue(S->MouseSensitivite);
    if (SliderBrightness)  SliderBrightness->SetValue(S->Brightness);


    SliderVolume->OnValueChanged.AddDynamic(this, &ULB_SettingUI::OnVolumeChanged);
    SliderSensitivity->OnValueChanged.AddDynamic(this, &ULB_SettingUI::OnSensitivityChanged);
    SliderBrightness->OnValueChanged.AddDynamic(this, &ULB_SettingUI::OnBrightnessChanged);

    auto FillQuality = [](UComboBoxString* Combo)
        {
            if (!Combo) return;
            Combo->ClearOptions();
            Combo->AddOption("Low");
            Combo->AddOption("Medium");
            Combo->AddOption("High");
            Combo->AddOption("Epic");
            Combo->AddOption("Cinematic");
            Combo->RefreshOptions();
        };

    FillQuality(ComboAA);
    FillQuality(ComboPost);
    FillQuality(ComboShadow);
    FillQuality(ComboTexture);

    if (ComboWindowMode)
    {
        ComboWindowMode->ClearOptions();
        ComboWindowMode->AddOption("Fullscreen");
        ComboWindowMode->AddOption("Windowed");
        ComboWindowMode->AddOption("WindowedFullscreen");
        ComboWindowMode->RefreshOptions();
    }

    if (ComboResolution)
    {
        ComboResolution->ClearOptions();
        ComboResolution->AddOption("360p");
        ComboResolution->AddOption("720p");
        ComboResolution->AddOption("1080p");
        ComboResolution->AddOption("1440p");
        ComboResolution->AddOption("2160p");
        ComboResolution->RefreshOptions();
    }

    if (ComboAA)       ComboAA->SetSelectedIndex(S->GetAntiAliasingQuality());
    if (ComboPost)     ComboPost->SetSelectedIndex(S->GetPostProcessingQuality());
    if (ComboShadow)   ComboShadow->SetSelectedIndex(S->GetShadowQuality());
    if (ComboTexture)  ComboTexture->SetSelectedIndex(S->GetTextureQuality());

    if (ComboWindowMode)
    {
        switch (S->GetFullscreenMode())
        {
        case EWindowMode::Fullscreen:         ComboWindowMode->SetSelectedOption("Fullscreen"); break;
        case EWindowMode::Windowed:           ComboWindowMode->SetSelectedOption("Windowed"); break;
        case EWindowMode::WindowedFullscreen: ComboWindowMode->SetSelectedOption("WindowedFullscreen"); break;
        }
    }

    if (ComboResolution)
    {
        FIntPoint Res = S->GetScreenResolution();
        if (Res == FIntPoint(640, 360))        ComboResolution->SetSelectedOption("360p");
        else if (Res == FIntPoint(1280, 720))  ComboResolution->SetSelectedOption("720p");
        else if (Res == FIntPoint(1920, 1080)) ComboResolution->SetSelectedOption("1080p");
        else if (Res == FIntPoint(2560, 1440)) ComboResolution->SetSelectedOption("1440p");
        else if (Res == FIntPoint(3840, 2160)) ComboResolution->SetSelectedOption("2160p");
        else ComboResolution->SetSelectedOption("1080p"); // ±âº»°ª
    }

    if (ButtonApply) ButtonApply->OnClicked.AddDynamic(this, &ULB_SettingUI::OnApplyClicked);
    if (ButtonReset) ButtonReset->OnClicked.AddDynamic(this, &ULB_SettingUI::OnResetClicked);

    if (ComboAA)       ComboAA->OnSelectionChanged.AddDynamic(this, &ULB_SettingUI::OnAAChanged);
    if (ComboPost)     ComboPost->OnSelectionChanged.AddDynamic(this, &ULB_SettingUI::OnPostChanged);
    if (ComboShadow)   ComboShadow->OnSelectionChanged.AddDynamic(this, &ULB_SettingUI::OnShadowChanged);
    if (ComboTexture)  ComboTexture->OnSelectionChanged.AddDynamic(this, &ULB_SettingUI::OnTextureChanged);
    if (ComboWindowMode) ComboWindowMode->OnSelectionChanged.AddDynamic(this, &ULB_SettingUI::OnWindowModeChanged);
    if (ComboResolution) ComboResolution->OnSelectionChanged.AddDynamic(this, &ULB_SettingUI::OnResolutionChanged);

    SynchronizeProperties();
}

void ULB_SettingUI::OnVolumeChanged(float Value)
{
    ULB_Setting::Get()->MasterVolume = Value;
    ULB_Setting::Get()->ApplyCustomSettings();
}

void ULB_SettingUI::OnSensitivityChanged(float Value)
{
    ULB_Setting::Get()->MouseSensitivite = Value;
}

void ULB_SettingUI::OnBrightnessChanged(float Value)
{
    ULB_Setting::Get()->Brightness = Value;
    ULB_Setting::Get()->ApplyCustomSettings();
}

void ULB_SettingUI::OnResolutionChanged(FString Item, ESelectInfo::Type)
{
    FIntPoint Res(1920, 1080);
    if (Item == "360p")   Res = FIntPoint(640, 360);
    if (Item == "720p")   Res = FIntPoint(1280, 720);
    if (Item == "1080p")  Res = FIntPoint(1920, 1080);
    if (Item == "1440p")  Res = FIntPoint(2560, 1440);
    if (Item == "2160p")  Res = FIntPoint(3840, 2160);
    ULB_Setting::Get()->SetScreenResolution(Res);
}

void ULB_SettingUI::OnWindowModeChanged(FString Item, ESelectInfo::Type)
{
    if (Item == "Fullscreen")         ULB_Setting::Get()->SetFullscreenMode(EWindowMode::Fullscreen);
    else if (Item == "Windowed")      ULB_Setting::Get()->SetFullscreenMode(EWindowMode::Windowed);
    else if (Item == "WindowedFullscreen") ULB_Setting::Get()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
}

void ULB_SettingUI::OnAAChanged(FString Item, ESelectInfo::Type) { ULB_Setting::Get()->SetAntiAliasingQuality(ParseQuality(Item)); }
void ULB_SettingUI::OnPostChanged(FString Item, ESelectInfo::Type) { ULB_Setting::Get()->SetPostProcessingQuality(ParseQuality(Item)); }
void ULB_SettingUI::OnShadowChanged(FString Item, ESelectInfo::Type) { ULB_Setting::Get()->SetShadowQuality(ParseQuality(Item)); }
void ULB_SettingUI::OnTextureChanged(FString Item, ESelectInfo::Type) { ULB_Setting::Get()->SetTextureQuality(ParseQuality(Item)); }

void ULB_SettingUI::OnApplyClicked()
{
    ULB_Setting::Get()->SaveSettings();
    ULB_Setting::Get()->ApplySettings(false);
}

void ULB_SettingUI::OnResetClicked()
{
    ULB_Setting::Get()->ResetToDefaults();

    ULB_Setting* S = ULB_Setting::Get();
    if (S)
    {
        if (SliderVolume)      SliderVolume->SetValue(S->MasterVolume);
        if (SliderSensitivity) SliderSensitivity->SetValue(S->MouseSensitivite);

        if (SliderBrightness)  SliderBrightness->SetValue(S->Brightness);

        if (ComboAA)       ComboAA->SetSelectedIndex(S->GetAntiAliasingQuality());
        if (ComboPost)     ComboPost->SetSelectedIndex(S->GetPostProcessingQuality());
        if (ComboShadow)   ComboShadow->SetSelectedIndex(S->GetShadowQuality());
        if (ComboTexture)  ComboTexture->SetSelectedIndex(S->GetTextureQuality());
    }
}

int32 ULB_SettingUI::ParseQuality(const FString& Item) const
{
    if (Item.Contains("Low"))       return 0;
    if (Item.Contains("Medium"))    return 1;
    if (Item.Contains("High"))      return 2;
    if (Item.Contains("Epic"))      return 3;
    if (Item.Contains("Cinematic")) return 4;
    return 2;
}

void ULB_SettingUI::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    auto FillQuality = [](UComboBoxString* Combo)
        {
            if (!Combo) return;
            Combo->ClearOptions();
            Combo->AddOption("Low");
            Combo->AddOption("Medium");
            Combo->AddOption("High");
            Combo->AddOption("Epic");
            Combo->AddOption("Cinematic");
            Combo->RefreshOptions();
        };

    FillQuality(ComboAA);
    ComboAA->RefreshOptions();
    FillQuality(ComboPost);
    ComboPost->RefreshOptions();
    FillQuality(ComboShadow);
    ComboShadow->RefreshOptions();
    FillQuality(ComboTexture);
    ComboTexture->RefreshOptions();
}