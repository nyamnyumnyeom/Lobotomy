#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"
#include "LB_Setting.generated.h"


UCLASS()
class LOBOTOMY_API ULB_Setting : public UGameUserSettings
{
	GENERATED_BODY()

public:
    /** Custom settings */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
    float MouseSensitivite = 1.0f; // 0.1 ~ 5.0

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
    float MasterVolume = 1.0f;     // 0.0 ~ 1.0

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
    float SFXVolume = 1.0f;        // 0.0 ~ 1.0, 효과음(SFX) 볼륨

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
    float BGMVolume = 1.0f;        // 0.0 ~ 1.0, 배경음(BGM) 볼륨

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
    float Brightness = 0.25f;       // 

    /** Reference to Master SoundClass (에디터에서 할당 가능) */
    //UPROPERTY(EditDefaultsOnly, Category = "Audio")
    TSoftObjectPtr<USoundClass> MasterSoundClass;

    /** Reference to SFX SoundClass (ALB_PlayerController에서 할당) */
    TSoftObjectPtr<USoundClass> SFXSoundClass;

    /** Reference to BGM SoundClass (ALB_PlayerController에서 할당) */
    TSoftObjectPtr<USoundClass> BGMSoundClass;

    /** Custom settings 적용 */
    UFUNCTION(BlueprintCallable)
    void ApplyCustomSettings();

    /** 세팅 전체 적용 */
    virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;
    virtual void LoadSettings(bool bForceReload = false) override;
    virtual void SaveSettings() override;

    /** 기본값으로 초기화 */
    UFUNCTION(BlueprintCallable)
    void ResetToDefaults();

    /** Static getter */
    static ULB_Setting* Get() { return Cast<ULB_Setting>(UGameUserSettings::GetGameUserSettings()); }
};