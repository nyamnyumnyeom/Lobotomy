#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI/LB_ItemData.h"
#include "LB_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;
class USoundBase;
class UInteractComponent;
class UAudioComponent;
class UInGameHUD;

UCLASS()
class LOBOTOMY_API ALB_Character : public ACharacter
{
    GENERATED_BODY()

public:
    ALB_Character();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FirstPersonCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Interact(const FInputActionValue& Value);
    void StartSprint();
    void StopSprint();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void HandleChart();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnEscapeToggle();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void HandleEscape(const FInputActionValue& Value);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void Dropaction();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    TArray<TObjectPtr<USoundBase>> FootstepSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    float FootstepDistanceThreshold;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    float NoiseLoudness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
    TSubclassOf<UCameraShakeBase> WalkShakeClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
    TSubclassOf<UCameraShakeBase> RunShakeClass;

    void StartWalking();

    void StartRunning();

    void StopMoving();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionTraceDistance = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionSphereRadius = 0;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Interaction")
    TObjectPtr<AActor> CurrentInteractActor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float Sensitive = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float Stamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float MaxStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float StaminaDrainRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float StaminaRecoverRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    float MinSprintStamina;

    bool bWantsToSprint;


private:
    bool bIsWalking;
    bool bIsRunning;

    bool bWasWalking;
    bool bWasRunning;
    float DistanceTraveled;

//심장소리로직
public:
    void StartHeartbeat();
    void StopHeartbeat();
    void SetHeartbeatTarget(AActor* NewTarget);
	void ResetHeartbeatTarget();

protected:

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* HeartbeatSound;

    UPROPERTY()
    TObjectPtr<UAudioComponent> HeartbeatAudioComponent = nullptr;

    UPROPERTY()
    TObjectPtr<AActor> HeartbeatTarget;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MinDistance = 300.0f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MaxDistance = 2500.0f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MinVolume = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MaxVolume = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MinPitch = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MaxPitch = 1.5f;

    UFUNCTION(BlueprintImplementableEvent, Category = "Flashlight")
    void ToggleFlashlight_BP();

public:

    UPROPERTY(EditAnywhere, Category = "Flashlight")
    bool IsFlashcanon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battery")
    float BatteryLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HUDUIClass;

    UPROPERTY(BlueprintReadOnly, Category = "UI")
    UUserWidget* HUDUIInstance;

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowHUDUI();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideHUDUI();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
    FName CurrentItem;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void PickupItem(FName ItemName);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnInventoryUpdated(FName NewItem);

    UFUNCTION(BlueprintCallable, Category = "Battery")
    void AddBattery(float Amount);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void ShowNoPickup();

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void Noitemuse();

private:
    bool bIsHUDVisible;

	// ---------- 플레이어 게임 오버 ----------
public:
	// 전기톱에게 사망시의 카메라 시퀀스 재생 (TargetLocation : 바라볼 액터의 위치)
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCameraDeathSequence(FVector TargetLocation);

	// 노커에게 사망시의 카메라 시퀀스 재생
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathSequence_Knocker();

	// 끼끼기에게 사망시의 카메라 시퀀스 재생
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathSequence_KKE();

	// 곰탱이에게 사망시의 카메라 시퀀스 재생
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathSequence_Bear(FVector TargetLocation);

	// 낮에 시간 초과 사망시의 로직
	UFUNCTION(BlueprintImplementableEvent)
	void OnDayDeathLogic();

	// 밤에 시간 초과 사망시의 로직
	UFUNCTION(BlueprintImplementableEvent)
	void OnNightDeathLogic();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateDeathUI();

    UFUNCTION(BlueprintImplementableEvent)
    void Timeout();

    UFUNCTION(BlueprintImplementableEvent)
    void Buzzover();

	// ---------- -------------------- ----------

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    UDataTable* ItemData;
    // --------------------  아이템 사용 ---------------------------------------ㅅㅂ
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UseItem();

    UFUNCTION()
    void HandleUseItem(const FInputActionValue& Value);

    UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
    void OnDoorUnlockFailed();

    UFUNCTION(BlueprintCallable, Category = "Item")
    void ClearCurrentItem();

    UFUNCTION(BlueprintCallable, Category = "Item")
    AActor* SpawnCurrentItem();

public:
    UFUNCTION(BlueprintCallable, Category = "Item")
    UClass* GetCurrentItemClass() const;

    const FItemRow* GetCurrentItemData() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
    float Sanity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
    float MaxSanity = 100.0f;

    UFUNCTION(BlueprintImplementableEvent, Category = "Sanity")
    void OnSanityChanged(float NewSanity);

    //정신력 증가, 감소 함수
    UFUNCTION(BlueprintCallable, Category = "Sanity")
    void AddSanity(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Sanity")
    void ReduceSanity(float Amount);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
    float SanityIntervalMin = 10.0f;   // 상태이상 발현 최소 초수

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
    float SanityIntervalMax = 100.0f;  // 상태이상 발현 최대 초수

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sanity")
    float SanityEffectTimer = -1.0f; // 상태이상 타이머

    //왜곡 효과는 여기에
    UFUNCTION(BlueprintImplementableEvent, Category = "Sanity")
    void PlaySanityDistortionEffect();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Time")
    bool IsNight() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    TArray<TObjectPtr<USoundBase>> Water_walk_Sound;

    bool IsInWaterArea() const;
private:

    void UpdateSanityEffect(float DeltaTime);
   // bool TryUseKeyOnCurrentDoor();
};