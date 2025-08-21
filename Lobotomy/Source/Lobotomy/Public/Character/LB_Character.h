#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LB_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;
class USoundBase;

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
    void StartSprint();
    void StopSprint();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    TArray<TObjectPtr<USoundBase>> FootstepSounds;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    float FootstepDistanceThreshold;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio|Footsteps")
    float NoiseLoudness;
private:
    float DistanceTraveled;
};