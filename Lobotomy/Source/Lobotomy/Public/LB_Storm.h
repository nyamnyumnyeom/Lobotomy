#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_Storm.generated.h"

class UAudioComponent;
class USoundBase;
class ADirectionalLight;

UCLASS()
class LOBOTOMY_API ALB_Storm : public AActor
{
	GENERATED_BODY()

public:
	ALB_Storm();

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void StartStorm();

	UFUNCTION(BlueprintCallable)
	void StopStorm();

private:

	UPROPERTY(EditAnywhere, Category = "Storm")
	UAudioComponent* RainAudio;

	UPROPERTY(EditAnywhere, Category = "Storm")
	UAudioComponent* ThunderAudio;

	UPROPERTY(EditAnywhere, Category = "Storm")
	USoundBase* RainSound;

	UPROPERTY(EditAnywhere, Category = "Storm")
	TArray<USoundBase*> ThunderSounds;

	UPROPERTY(EditAnywhere, Category = "Storm")
	ADirectionalLight* SunLight;

	UPROPERTY(EditAnywhere, Category = "Storm")
	float LightningIntensity = 100000.f;

	float DefaultLightIntensity;

	bool bStormActive = false;

	FTimerHandle StormTimer;
	FTimerHandle ThunderTimer;

	TArray<FTimerHandle> FlashTimers;

	void ScheduleNextLightning();
	void TriggerLightning();
	void FlashLightning(int32 FlashCount);
	void PlayThunder();
};