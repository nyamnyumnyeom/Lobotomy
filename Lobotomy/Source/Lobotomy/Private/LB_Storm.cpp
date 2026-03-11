#include "LB_Storm.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ALB_Storm::ALB_Storm()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RainAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("RainAudio"));
	RainAudio->SetupAttachment(RootComponent);
	RainAudio->bAutoActivate = false;

	ThunderAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ThunderAudio"));
	ThunderAudio->SetupAttachment(RootComponent);
	ThunderAudio->bAutoActivate = false;
}

void ALB_Storm::BeginPlay()
{
	Super::BeginPlay();

	if (RainSound)
	{
		RainAudio->SetSound(RainSound);
	}

	if (SunLight)
	{
		DefaultLightIntensity = SunLight->GetLightComponent()->Intensity;
	}
}

void ALB_Storm::StartStorm()
{
	if (bStormActive) return;

	bStormActive = true;

	if (RainAudio)
	{
		RainAudio->FadeIn(10.f, 1.f);
	}

	ScheduleNextLightning();
}

void ALB_Storm::StopStorm()
{
	if (!bStormActive) return;

	bStormActive = false;

	GetWorldTimerManager().ClearTimer(StormTimer);
	GetWorldTimerManager().ClearTimer(ThunderTimer);

	for (FTimerHandle& Handle : FlashTimers)
	{
		GetWorldTimerManager().ClearTimer(Handle);
	}

	FlashTimers.Empty();

	if (RainAudio)
	{
		RainAudio->FadeOut(10.f, 0.f);
	}
}

void ALB_Storm::ScheduleNextLightning()
{
	if (!bStormActive) return;

	float Delay = FMath::FRandRange(15.f, 30.f);

	GetWorldTimerManager().SetTimer(
		StormTimer,
		this,
		&ALB_Storm::TriggerLightning,
		Delay,
		false
	);
}

void ALB_Storm::TriggerLightning()
{
	if (!bStormActive) return;

	int32 FlashCount = FMath::RandRange(1, 3);

	FlashLightning(FlashCount);

	float ThunderDelay = FMath::FRandRange(1.f, 3.f);

	FTimerHandle ThunderHandle;

	GetWorldTimerManager().SetTimer(
		ThunderHandle,
		this,
		&ALB_Storm::PlayThunder,
		ThunderDelay,
		false
	);

	ScheduleNextLightning();
}

void ALB_Storm::FlashLightning(int32 FlashCount)
{
	if (!SunLight) return;

	ULightComponent* LightComp = SunLight->GetLightComponent();

	float TimeOffset = 0.f;

	for (int32 i = 0; i < FlashCount; i++)
	{
		FTimerHandle FlashOn;
		FTimerHandle FlashOff;

		GetWorldTimerManager().SetTimer(
			FlashOn,
			[this, LightComp]()
			{
				if (!bStormActive) return;
				LightComp->SetIntensity(LightningIntensity);
			},
			TimeOffset,
			false
		);

		GetWorldTimerManager().SetTimer(
			FlashOff,
			[this, LightComp]()
			{
				if (!bStormActive) return;
				LightComp->SetIntensity(DefaultLightIntensity);
			},
			TimeOffset + 0.2f,
			false
		);

		FlashTimers.Add(FlashOn);
		FlashTimers.Add(FlashOff);

		TimeOffset += FMath::FRandRange(0.07f, 0.15f);
	}
}

void ALB_Storm::PlayThunder()
{
	if (!bStormActive) return;

	if (ThunderSounds.Num() == 0) return;

	int32 Index = FMath::RandRange(0, ThunderSounds.Num() - 1);

	if (ThunderAudio)
	{
		ThunderAudio->SetSound(ThunderSounds[Index]);
		ThunderAudio->Play();
	}
}