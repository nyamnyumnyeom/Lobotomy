#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_ObstaclePush.generated.h"

class UTextBlock;

UCLASS()
class LOBOTOMY_API ALB_ObstaclePush : public AActor
{
    GENERATED_BODY()

public:
    ALB_ObstaclePush();

    virtual void Tick(float DeltaSeconds) override;

public:
    // 위치 값
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
    float LocationU = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
    float LocationV = 100.f;

    // 설정 값
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float MaxOffset = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float TimeUpTime = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float TimeRequired = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float TimerDelay = 0.016f;

protected:
    // 미니게임 상태
    bool bMiniGameActive = false;
    float MiniGameElapsed = 0.f;

    // Hover 시간
    bool bHoverActive = false;
    float HoveredTime = 0.f;

    // U 이동
    bool bMoveUActive = false;
    float MaxLocationU = 300.f;
    float StartValue_U;
    float TargetValue_U;
    float ChangeDuration_U;
    float ElapsedTime_U;

    // V 이동
    bool bMoveVActive = false;
    float MaxLocationV = 300.f;
    float StartValue_V;
    float TargetValue_V;
    float ChangeDuration_V;
    float ElapsedTime_V;

public:
    UFUNCTION(BlueprintCallable)
    void StartMiniGameTimer();

    UFUNCTION(BlueprintCallable)
    void EndMiniGameTimer(bool& Result);

    UFUNCTION(BlueprintCallable)
    void HoveredTimeResume();

    UFUNCTION(BlueprintCallable)
    void HoveredTimePause();

    UFUNCTION(BlueprintImplementableEvent)
    void TimeOver();

    UFUNCTION(BlueprintCallable)
    void StartChange_U(float MaxU);

    UFUNCTION(BlueprintCallable)
    void StartChange_V(float MaxV);

    UFUNCTION(BlueprintCallable)
    void StopMovingTimer();

    UFUNCTION(BlueprintImplementableEvent)
    void OnUpdateLocation();

    UFUNCTION(BlueprintCallable)
    float GetRemainingTime() const;

    UFUNCTION(BlueprintCallable)
    bool IsWarningTime() const;

    UFUNCTION(BlueprintCallable)
    float GetHoveredTime() const { return HoveredTime; }
};