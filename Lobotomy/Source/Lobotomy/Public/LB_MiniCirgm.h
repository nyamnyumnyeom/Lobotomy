// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LB_MiniCirgm.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ULB_MiniCirgm : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniGame")
    float RotateSpeed = 120.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MiniGame")
    float PointerAngle = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MiniGame")
    float SuccessStartAngle = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MiniGame")
    float SuccessEndAngle = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniGame")
    float SuccessZoneSize = 30.f;

    UPROPERTY(BlueprintReadOnly)
    bool bIsPlaying = false;

    UPROPERTY(meta = (BindWidget))
    class UImage* Pointer;

    UPROPERTY(meta = (BindWidget))
    class UImage* SuccessZone;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ResultText;

public:
    UFUNCTION(BlueprintCallable)
    void StartMiniGame();

    UFUNCTION(BlueprintCallable)
    void StopMiniGame();

    UFUNCTION(BlueprintCallable)
    void OnInputPressed();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentRound = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredSuccessCount = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SuccessCount = 0;

    UFUNCTION(BlueprintImplementableEvent)
    void OnMiniGameCleared();

    UFUNCTION(BlueprintImplementableEvent)
    void OnMiniGameFail();

    UFUNCTION(BlueprintImplementableEvent)
    void Soundcall();

private:
    void UpdatePointer(float DeltaTime);
    void SpawnRandomSuccessZone();
    void CheckSuccess();
};
