#include "LB_Setting.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Sound/SoundClass.h"
#include "Misc/ConfigCacheIni.h"
#include "EngineUtils.h"
#include "Engine/PostProcessVolume.h"
#include "Character/LB_PlayerController.h"

void ULB_Setting::ApplyCustomSettings()
{
    // -------------------
    // 1. 볼륨 (UGameUserSettings가 관리 안 함 -> 직접 구현)
    if (USoundClass* SC = MasterSoundClass.LoadSynchronous())
    {
        SC->Properties.Volume = FMath::Clamp(MasterVolume, 0.f, 2.f);
    }

    // 1-1. 효과음(SFX) / 배경음(BGM) 개별 볼륨
    if (USoundClass* SFXSC = SFXSoundClass.LoadSynchronous())
    {
        SFXSC->Properties.Volume = FMath::Clamp(SFXVolume, 0.f, 2.f);
    }

    if (USoundClass* BGMSC = BGMSoundClass.LoadSynchronous())
    {
        BGMSC->Properties.Volume = FMath::Clamp(BGMVolume, 0.f, 2.f);
    }

    // -------------------
    // 2. 밝기 (UGameUserSettings가 관리 안 함 -> 직접 구현)
    // r.Color.Mid는 감마/중간톤 조절이므로 계속 사용 가능
    float TargetMid = FMath::GetMappedRangeValueClamped(
        FVector2D(0.f, 1.f),    // 입력 범위 (슬라이더)
        FVector2D(0.8f, 1.5f),  // 출력 범위
        Brightness              // 현재 슬라이더 값
    );

	// 설정된 밝기 값을 실제로 적용하는 로직
	// UGameUserSettings 클래스는 월드에 속해있지 않기 때문에 단순 GetWorld() 함수로는 nullptr을 반환함.
	// 때문에 월드를 가져오는 로직 추가함.
	UWorld* World = nullptr;
	if (GEngine)
	{
		for (const FWorldContext& Context : GEngine->GetWorldContexts())
		{
			if (Context.WorldType == EWorldType::Game || Context.WorldType == EWorldType::PIE)
			{
				World = Context.World();
				break;
			}
		}
	}

	if (World)
	{
		for (TActorIterator<APostProcessVolume> It(World); It; ++It)
		{
			APostProcessVolume* PPVolume = *It;
			if (PPVolume)
			{
				PPVolume->Settings.AutoExposureBias = TargetMid;
			}
		}

		if (GEngine && World)
		{
			GEngine->Exec(GetWorld(), *FString::Printf(TEXT("r.Color.Mid %.3f"), TargetMid));
		}
	}

    // -------------------
    // 3. 마우스 감도 (UGameUserSettings가 관리 안 함 -> 직접 구현)
    if (World)
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (ALB_PlayerController* LPC = Cast<ALB_PlayerController>(PC))
            {
                LPC->SetMouseSensitivite(MouseSensitivite);
            }
        }
    }

    // [중요]
    // 그래픽 품질(sg.*)과 해상도(r.SetRes) 관련 코드는 
    // Super::ApplySettings()에서 자동으로 처리하므로 모두 삭제했습니다.
}

void ULB_Setting::ApplySettings(bool bCheckForCommandLineOverrides)
{
    // 1. 엔진 기본 설정 적용 (해상도, 전체화면, 그래픽 품질 등)
    // 이 함수가 내부적으로 Scalability::SetQualityLevels를 호출하여 렌더링에 반영합니다.
    Super::ApplySettings(bCheckForCommandLineOverrides);

    // 2. 내 커스텀 설정 적용 (볼륨, 밝기, 감도)
    ApplyCustomSettings();
}

void ULB_Setting::LoadSettings(bool bForceReload)
{
    // 1. 엔진 기본 설정 로드 (GameUserSettings.ini에서 자동으로 읽어옴)
    Super::LoadSettings(bForceReload);

    // 2. 커스텀 값만 추가로 로드
    // (TextureQuality 등은 Super::LoadSettings가 이미 로드했으므로 중복 로드 삭제)
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MouseSensitivity"), MouseSensitivite, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MasterVolume"), MasterVolume, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("SFXVolume"), SFXVolume, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("BGMVolume"), BGMVolume, GGameUserSettingsIni);
    GConfig->GetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("Brightness"), Brightness, GGameUserSettingsIni);

    // 3. 로드된 커스텀 값 즉시 적용
    ApplyCustomSettings();
}

void ULB_Setting::SaveSettings()
{
    // 1. 커스텀 값 저장
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MouseSensitivity"), MouseSensitivite, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("MasterVolume"), MasterVolume, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("SFXVolume"), SFXVolume, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("BGMVolume"), BGMVolume, GGameUserSettingsIni);
    GConfig->SetFloat(TEXT("/Script/Lobotomy.LB_Setting"), TEXT("Brightness"), Brightness, GGameUserSettingsIni);

    // 2. 엔진 기본 설정 저장 (TextureQuality, Resolution 등은 Super가 알아서 저장함)
    Super::SaveSettings();

    // GConfig->Flush는 Super::SaveSettings 내부에서도 호출될 수 있으나, 확실하게 하기 위해 둬도 무방합니다.
    GConfig->Flush(false, GGameUserSettingsIni);
}

void ULB_Setting::ResetToDefaults()
{
    Super::SetToDefaults();

    MouseSensitivite = 1.0f;
    MasterVolume = 1.0f;
    SFXVolume = 1.0f;
    BGMVolume = 1.0f;
    Brightness = 0.5f;

    ApplySettings(false);
    SaveSettings();
}