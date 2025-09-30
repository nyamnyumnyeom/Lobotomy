#include "LB_Setting.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Sound/SoundClass.h"
#include "Misc/ConfigCacheIni.h"

void ULB_Setting::ApplyCustomSettings()
{
    // -------------------
    // 1. 볼륨
    if (USoundClass* SC = MasterSoundClass.LoadSynchronous())
    {
        SC->Properties.Volume = FMath::Clamp(MasterVolume, 0.f, 1.f);
    }

    // -------------------
    // 2. 밝기
    const float Mid = FMath::Clamp(Brightness, 0.5f, 1.5f);
    if (GEngine && GetWorld())
    {
        GEngine->Exec(GetWorld(), *FString::Printf(TEXT("r.Color.Mid %.3f"), Mid));
    }

    // -------------------
    // 3. 마우스 감도
    // (ALB_PlayerController에서 Apply할 때 LookAction에 곱해주는 방식 사용)

    // -------------------
    // 4. 그래픽 품질 적용
    if (GetWorld() && GEngine)
    {
        FString Cmd;

        Cmd = FString::Printf(TEXT("sg.AntiAliasingQuality %d"), GetAntiAliasingQuality());
        GEngine->Exec(GetWorld(), *Cmd);

        Cmd = FString::Printf(TEXT("sg.PostProcessQuality %d"), GetPostProcessingQuality());
        GEngine->Exec(GetWorld(), *Cmd);

        Cmd = FString::Printf(TEXT("sg.ShadowQuality %d"), GetShadowQuality());
        GEngine->Exec(GetWorld(), *Cmd);

        Cmd = FString::Printf(TEXT("sg.TextureQuality %d"), GetTextureQuality());
        GEngine->Exec(GetWorld(), *Cmd);

        // 전체 스케일러빌리티 적용
        Cmd = FString::Printf(TEXT("sg.SetOverallQualityLevel %d"), GetOverallScalabilityLevel());
        GEngine->Exec(GetWorld(), *Cmd);
    }

    // -------------------
    // 5. 해상도 & 화면 모드 적용
    const FIntPoint Res = GetScreenResolution();
    const EWindowMode::Type WinMode = GetFullscreenMode();
    FString FullscreenCmd;

    switch (WinMode)
    {
    case EWindowMode::Fullscreen:        FullscreenCmd = TEXT("Fullscreen"); break;
    case EWindowMode::Windowed:          FullscreenCmd = TEXT("Windowed"); break;
    case EWindowMode::WindowedFullscreen:FullscreenCmd = TEXT("WindowedFullscreen"); break;
    default: FullscreenCmd = TEXT("Windowed"); break;
    }

    FString ResolutionCmd = FString::Printf(TEXT("r.SetRes %dx%d%s"), Res.X, Res.Y, *FullscreenCmd);
    if (GEngine && GetWorld())
    {
        GEngine->Exec(GetWorld(), *ResolutionCmd);
    }
}

void ULB_Setting::ApplySettings(bool bCheckForCommandLineOverrides)
{
    Super::ApplySettings(bCheckForCommandLineOverrides);
    ApplyCustomSettings();
}

void ULB_Setting::LoadSettings(bool bForceReload)
{
    Super::LoadSettings(bForceReload);

    // -------------------
    // 기존 커스텀 값 불러오기
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MouseSensitivity"), MouseSensitivity, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MasterVolume"), MasterVolume, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("Brightness"), Brightness, GGameUserSettingsIni);

    int32 Temp;
    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("AntiAliasingQuality"), Temp, GGameUserSettingsIni);
    SetAntiAliasingQuality(Temp);

    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("PostProcessingQuality"), Temp, GGameUserSettingsIni);
    SetPostProcessingQuality(Temp);

    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("ShadowQuality"), Temp, GGameUserSettingsIni);
    SetShadowQuality(Temp);

    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("TextureQuality"), Temp, GGameUserSettingsIni);
    SetTextureQuality(Temp);

    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("OverallScalabilityLevel"), Temp, GGameUserSettingsIni);
    SetOverallScalabilityLevel(Temp);

    // 해상도
    int32 Width = 1920, Height = 1080;
    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("ScreenWidth"), Width, GGameUserSettingsIni);
    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("ScreenHeight"), Height, GGameUserSettingsIni);
    SetScreenResolution(FIntPoint(Width, Height));

    // 화면 모드
    int32 ModeInt = 1;
    GConfig->GetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("FullscreenMode"), ModeInt, GGameUserSettingsIni);
    SetFullscreenMode(static_cast<EWindowMode::Type>(ModeInt));
}

void ULB_Setting::SaveSettings()
{
    Super::SaveSettings();

    // -------------------
    // 커스텀 값 저장
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MouseSensitivity"), MouseSensitivity, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MasterVolume"), MasterVolume, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("Brightness"), Brightness, GGameUserSettingsIni);

    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("AntiAliasingQuality"), GetAntiAliasingQuality(), GGameUserSettingsIni);
    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("PostProcessingQuality"), GetPostProcessingQuality(), GGameUserSettingsIni);
    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("ShadowQuality"), GetShadowQuality(), GGameUserSettingsIni);
    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("TextureQuality"), GetTextureQuality(), GGameUserSettingsIni);
    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("OverallScalabilityLevel"), GetOverallScalabilityLevel(), GGameUserSettingsIni);

    FIntPoint Res = GetScreenResolution();
    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("ScreenWidth"), Res.X, GGameUserSettingsIni);
    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("ScreenHeight"), Res.Y, GGameUserSettingsIni);

    GConfig->SetInt(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("FullscreenMode"), static_cast<int32>(GetFullscreenMode()), GGameUserSettingsIni);

    GConfig->Flush(false, GGameUserSettingsIni);
}

void ULB_Setting::ResetToDefaults()
{
    MouseSensitivity = 1.0f;
    MasterVolume = 1.0f;
    Brightness = 1.0f;

    SetOverallScalabilityLevel(2); // 중간
    SetAntiAliasingQuality(2);
    SetPostProcessingQuality(2);
    SetShadowQuality(2);
    SetTextureQuality(2);

    SetScreenResolution(FIntPoint(1920, 1080));
    SetFullscreenMode(EWindowMode::Windowed);

    SaveSettings();
    ApplySettings(false);
}