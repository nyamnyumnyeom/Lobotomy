#include "UI/LB_SettingUI.h"
#include "LB_Setting.h"
#include "Character/LB_PlayerController.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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

	FText NewVolumeText = FText::AsNumber(S->MasterVolume);
	if (TextVolume)      TextVolume->SetText(NewVolumeText);
	FText NewBrightnessText = FText::AsNumber(S->Brightness);
	if (TextBrightness)  TextBrightness->SetText(NewBrightnessText);
	FText NewSensitivityText = FText::AsNumber(S->MouseSensitivite);
	if (TextSensitivity) TextSensitivity->SetText(NewSensitivityText);


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
        else ComboResolution->SetSelectedOption("1080p"); // 기본값
    }

	// "Antialiasing, PostProcessing, Shadow, Texture" 설정값이 표기되는 로직 추가
	if (ComboAA)
	{
		switch (S->GetAntiAliasingQuality())
		{
		case 0:			     ComboAA->SetSelectedOption("Low"); break;
		case 1:			     ComboAA->SetSelectedOption("Medium"); break;
		case 2:				 ComboAA->SetSelectedOption("High"); break;
		case 3:				 ComboAA->SetSelectedOption("Epic"); break;
		case 4:				 ComboAA->SetSelectedOption("Cinematic"); break;
		}
	}

	if (ComboPost)
	{
		switch (S->GetPostProcessingQuality())
		{
		case 0:			     ComboPost->SetSelectedOption("Low"); break;
		case 1:			     ComboPost->SetSelectedOption("Medium"); break;
		case 2:				 ComboPost->SetSelectedOption("High"); break;
		case 3:				 ComboPost->SetSelectedOption("Epic"); break;
		case 4:				 ComboPost->SetSelectedOption("Cinematic"); break;
		}
	}

	if (ComboShadow)
	{
		switch (S->GetShadowQuality())
		{
		case 0:			     ComboShadow->SetSelectedOption("Low"); break;
		case 1:			     ComboShadow->SetSelectedOption("Medium"); break;
		case 2:				 ComboShadow->SetSelectedOption("High"); break;
		case 3:				 ComboShadow->SetSelectedOption("Epic"); break;
		case 4:				 ComboShadow->SetSelectedOption("Cinematic"); break;
		}
	}

	if (ComboTexture)
	{
		switch (S->GetTextureQuality())
		{
		case 0:			     ComboTexture->SetSelectedOption("Low"); break;
		case 1:			     ComboTexture->SetSelectedOption("Medium"); break;
		case 2:				 ComboTexture->SetSelectedOption("High"); break;
		case 3:				 ComboTexture->SetSelectedOption("Epic"); break;
		case 4:				 ComboTexture->SetSelectedOption("Cinematic"); break;
		}
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

	FText NewText = FText::AsNumber(Value);
	if (TextVolume)      TextVolume->SetText(NewText);
}

void ULB_SettingUI::OnSensitivityChanged(float Value)
{
    ULB_Setting::Get()->MouseSensitivite = Value;

	FText NewText = FText::AsNumber(Value);
	if (TextSensitivity) TextSensitivity->SetText(NewText);
}

void ULB_SettingUI::OnBrightnessChanged(float Value)
{
    ULB_Setting::Get()->Brightness = Value;
    ULB_Setting::Get()->ApplyCustomSettings();

	FText NewText = FText::AsNumber(Value);
	if (TextBrightness)  TextBrightness->SetText(NewText);
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

    //auto FillQuality = [](UComboBoxString* Combo)
    //    {
    //        if (!Combo) return;
    //        Combo->ClearOptions();
    //        Combo->AddOption("Low");
    //        Combo->AddOption("Medium");
    //        Combo->AddOption("High");
    //        Combo->AddOption("Epic");
    //        Combo->AddOption("Cinematic");
    //        Combo->RefreshOptions();
    //    };

    //FillQuality(ComboAA);
    //ComboAA->RefreshOptions();
    //FillQuality(ComboPost);
    //ComboPost->RefreshOptions();
    //FillQuality(ComboShadow);
    //ComboShadow->RefreshOptions();
    //FillQuality(ComboTexture);
    //ComboTexture->RefreshOptions();
}