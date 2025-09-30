#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LB_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;
class USoundBase;
class UInteractComponent;
class UAudioComponent;

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
    void OnEscapeToggle();

    UFUNCTION()
    void HandleEscape(const FInputActionValue& Value);

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
    float InteractionTraceDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionSphereRadius;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Interaction")
    TObjectPtr<AActor> CurrentInteractActor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float Sensitive = 1.f;


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

protected:

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* HeartbeatSound;

    UPROPERTY()
    TObjectPtr<UAudioComponent> HeartbeatAudioComponent;

    UPROPERTY()
    TObjectPtr<AActor> HeartbeatTarget;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MinDistance = 10.f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MaxDistance = 250.f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MinVolume = 0.2f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MaxVolume = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MinPitch = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    float MaxPitch = 2.0f;
};