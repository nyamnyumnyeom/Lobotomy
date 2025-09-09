#include "LB_Setting.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Sound/SoundClass.h"
#include "Misc/ConfigCacheIni.h"

void ULB_Setting::ApplyCustomSettings()
{
    // 볼륨
    if (USoundClass* SC = MasterSoundClass.LoadSynchronous())
    {
        SC->Properties.Volume = FMath::Clamp(MasterVolume, 0.f, 1.f);
    }

    // 밝기 (톤매퍼 중간값)
    const float Mid = FMath::Clamp(Brightness, 0.5f, 1.5f);
    if (GEngine && GetWorld())
    {
        GEngine->Exec(GetWorld(), *FString::Printf(TEXT("r.Color.Mid %.3f"), Mid));
    }

    // 마우스 감도는 입력 처리에서 ULB_Setting::Get()->MouseSensitivity 값으로 적용
}

void ULB_Setting::ApplySettings(bool bCheckForCommandLineOverrides)
{
    Super::ApplySettings(bCheckForCommandLineOverrides);
    ApplyCustomSettings();
}

void ULB_Setting::LoadSettings(bool bForceReload)
{
    Super::LoadSettings(bForceReload);

    // Custom 값 불러오기
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MouseSensitivity"), MouseSensitivity, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MasterVolume"), MasterVolume, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("Brightness"), Brightness, GGameUserSettingsIni);
}

void ULB_Setting::SaveSettings()
{
    Super::SaveSettings();

    // Custom 값 저장
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MouseSensitivity"), MouseSensitivity, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MasterVolume"), MasterVolume, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("Brightness"), Brightness, GGameUserSettingsIni);

    GConfig->Flush(false, GGameUserSettingsIni);
}

void ULB_Setting::ResetToDefaults()
{
    // 기본값 세팅
    MouseSensitivity = 1.0f;
    MasterVolume = 1.0f;
    Brightness = 1.0f;

    // 그래픽 품질 기본값 (보통 중간 = 2)
    SetOverallScalabilityLevel(2);

    // 해상도 기본값 (1080p)
    SetScreenResolution(FIntPoint(1920, 1080));
    SetFullscreenMode(EWindowMode::Windowed);

    SaveSettings();
    ApplySettings(false);
}