#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_DroppropsBase.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class USoundBase;
class UPrimitiveComponent;

UCLASS()
class LOBOTOMY_API ALB_DroppropsBase : public AActor
{
    GENERATED_BODY()

public:
    ALB_DroppropsBase();

    UFUNCTION(BlueprintCallable, Category = "Drop")
    void Dropforce();

    UFUNCTION(BlueprintCallable, Category = "Drop")
    void ResetDropProps();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UArrowComponent* DropDirectionArrow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop Settings")
    float DropForceMagnitude = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    USoundBase* DropImpactSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float MinImpactStrengthForSound = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float ImpactSoundCooldown = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float MaxImpactStrengthForSound = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float MinVolumeMultiplier = 0.6f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float MaxVolumeMultiplier = 1.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float MinPitchMultiplier = 0.9f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Settings")
    float MaxPitchMultiplier = 1.1f;

    UFUNCTION()
    void OnMeshHit(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

private:
    UPROPERTY()
    TArray<UStaticMeshComponent*> CachedMeshComponents;

    TMap<TObjectPtr<UStaticMeshComponent>, FTransform> InitialMeshWorldTransforms;

    float LastImpactSoundTime = -1000.0f;
};