// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AchievementSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAchievement, Log, All);

UCLASS()
class LOBOTOMY_API UAchievementSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /**
     * 입력받은 ID에 해당하는 스팀 업적을 즉시 해금합니다.
     * @param AchievementID 스팀웍스 대시보드에 등록된 업적의 'API Name'
     */
    UFUNCTION(BlueprintCallable, Category = "Achievement")
    void UnlockAchievement(FName AchievementID);

};