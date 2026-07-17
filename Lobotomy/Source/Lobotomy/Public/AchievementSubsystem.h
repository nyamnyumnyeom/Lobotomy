// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AchievementSubsystem.generated.h"

UCLASS()
class LOBOTOMY_API UAchievementSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // 업적 잠금 해제
    UFUNCTION(BlueprintCallable, Category = "Achievement")
    void UnlockAchievement(FName AchievementID);

    // 스팀 통계(Stat) 값을 설정하는 함수
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void SetSteamStat(FName StatID, int32 Value);

};