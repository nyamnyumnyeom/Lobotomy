// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/LB_ObstaclePush.h"

// Sets default values
ALB_ObstaclePush::ALB_ObstaclePush()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALB_ObstaclePush::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALB_ObstaclePush::StartMiniGameTimer()
{
	GetWorldTimerManager().ClearTimer(MiniGameTimerHandle);

	HoveredTime = 0.0f;

	GetWorldTimerManager().SetTimer(MiniGameTimerHandle, this, &ALB_ObstaclePush::TimeOver, TimeUpTime, false);
}

void ALB_ObstaclePush::EndMiniGameTimer(bool &Result)
{
	GetWorldTimerManager().ClearTimer(HoverTimerHandle);
	GetWorldTimerManager().ClearTimer(MiniGameTimerHandle);

	if (HoveredTime >= TimeRequired)
	{
		Result = true;
	}
}

void ALB_ObstaclePush::HoveredTimeResume()
{
	GetWorldTimerManager().SetTimer(HoverTimerHandle, this, &ALB_ObstaclePush::UpdateHoveredTime, TimerDelay, true);
}

void ALB_ObstaclePush::HoveredTimePause()
{
	GetWorldTimerManager().ClearTimer(HoverTimerHandle);
}

void ALB_ObstaclePush::UpdateHoveredTime()
{
	HoveredTime += TimerDelay;

	if (HoveredTime >= TimeRequired)
	{
		TimeOver();
	}
}

void ALB_ObstaclePush::StartChange_U(float MaxU)
{
	GetWorldTimerManager().ClearTimer(LocationUTimerHandle);

	MaxLocationU = MaxU;

	float ChangeLocation = FMath::FRandRange(LocationU - MaxOffset, LocationU + MaxOffset);

	float NewLocation = FMath::Min(MaxLocationV, ChangeLocation);
	NewLocation = FMath::Max(100.0f, ChangeLocation);

	StartValue_U = LocationU;
	TargetValue_U = NewLocation;

	ChangeDuration_U = FMath::FRandRange(0.7f, 3.0f);
	ElapsedTime_U = 0.0f;

	GetWorldTimerManager().SetTimer(LocationUTimerHandle, this, &ALB_ObstaclePush::UpdateLocationU, TimerDelay, true);
}

void ALB_ObstaclePush::StartChange_V(float MaxV)
{
	GetWorldTimerManager().ClearTimer(LocationVTimerHandle);

	MaxLocationV = MaxV;

	float ChangeLocation = FMath::FRandRange(LocationV - MaxOffset, LocationV + MaxOffset);

	float NewLocation = FMath::Min(MaxLocationV, ChangeLocation);
	NewLocation = FMath::Max(100.0f, ChangeLocation);

	StartValue_V = LocationV;
	TargetValue_V = NewLocation;

	ChangeDuration_V = FMath::FRandRange(0.7f, 3.0f);
	ElapsedTime_V = 0.0f;

	GetWorldTimerManager().SetTimer(LocationVTimerHandle, this, &ALB_ObstaclePush::UpdateLocationV, TimerDelay, true);
}

void ALB_ObstaclePush::StopMovingTimer()
{
	GetWorldTimerManager().ClearTimer(LocationUTimerHandle);
	GetWorldTimerManager().ClearTimer(LocationVTimerHandle);
}

void ALB_ObstaclePush::UpdateLocationU()
{
	ElapsedTime_U += TimerDelay;

	float Alpha = FMath::Clamp(ElapsedTime_U / ChangeDuration_U, 0.f, 1.f);
	LocationU = FMath::Lerp(StartValue_U, TargetValue_U, Alpha);

	OnUpdateLocation();

	if (Alpha >= 1.f)
	{
		StartChange_U(MaxLocationU);
	}
}

void ALB_ObstaclePush::UpdateLocationV()
{
	ElapsedTime_V += TimerDelay;

	float Alpha = FMath::Clamp(ElapsedTime_V / ChangeDuration_V, 0.f, 1.f);
	LocationV = FMath::Lerp(StartValue_V, TargetValue_V, Alpha);

	if (Alpha >= 1.f)
	{
		StartChange_V(MaxLocationV);
	}
}
