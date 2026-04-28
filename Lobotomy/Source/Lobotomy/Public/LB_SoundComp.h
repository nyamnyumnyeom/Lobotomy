// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LB_SoundComp.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API ULB_SoundComp : public UActorComponent
{
    GENERATED_BODY()

public:
	ULB_SoundComp();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnMeshHit(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound")
    USoundBase* ImpactSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound")
    float MinImpactStrengthForSound = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound")
    float MaxImpactStrengthForSound = 3000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound")
    float ImpactSoundCooldown = 0.15f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound|Volume")
    float MinVolumeMultiplier = 0.4f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound|Volume")
    float MaxVolumeMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound|Pitch")
    float MinPitchMultiplier = 0.85f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Sound|Pitch")
    float MaxPitchMultiplier = 1.15f;

private:
    UPROPERTY()
    TArray<UStaticMeshComponent*> CachedMeshComponents;

    float LastImpactSoundTime = -1000.0f;
};