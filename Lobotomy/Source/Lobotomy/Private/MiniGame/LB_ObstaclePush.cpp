#include "MiniGame/LB_ObstaclePush.h"

ALB_ObstaclePush::ALB_ObstaclePush()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALB_ObstaclePush::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bMiniGameActive)
		return;

	if (bMiniGameActive)
	{
		MiniGameElapsed += DeltaTime;

		if (MiniGameElapsed >= TimeUpTime)
		{
			bMiniGameActive = false;
			TimeOver();
		}
	}
	if (bHoverActive)
	{
		HoveredTime += DeltaTime;

		if (HoveredTime >= TimeRequired)
		{
			HoveredTime = TimeRequired;
			TimeOver();
			bHoverActive = false;
		}
	}
	else
	{
		HoveredTime -= DeltaTime*2;
	}

	HoveredTime = FMath::Clamp(HoveredTime, 0.f, TimeRequired);

	if (bMoveUActive)
	{
		ElapsedTime_U += DeltaTime;
		float Alpha = FMath::Clamp(ElapsedTime_U / ChangeDuration_U, 0.f, 1.f);

		LocationU = FMath::Lerp(StartValue_U, TargetValue_U, Alpha);
		OnUpdateLocation();

		if (Alpha >= 1.f)
		{
			StartChange_U(MaxLocationU);
		}
	}

	if (bMoveVActive)
	{
		ElapsedTime_V += DeltaTime;
		float Alpha = FMath::Clamp(ElapsedTime_V / ChangeDuration_V, 0.f, 1.f);

		LocationV = FMath::Lerp(StartValue_V, TargetValue_V, Alpha);
		OnUpdateLocation();

		if (Alpha >= 1.f)
		{
			StartChange_V(MaxLocationV);
		}
	}
}

void ALB_ObstaclePush::StartMiniGameTimer()
{
	bMiniGameActive = true;
	MiniGameElapsed = 0.f;

	HoveredTime = 0.f;
}

void ALB_ObstaclePush::EndMiniGameTimer(bool& Result)
{
	bMiniGameActive = false;
	bHoverActive = false;

	Result = (HoveredTime >= TimeRequired);
}

void ALB_ObstaclePush::HoveredTimeResume()
{
	bHoverActive = true;
}

void ALB_ObstaclePush::HoveredTimePause()
{
	bHoverActive = false;
}

void ALB_ObstaclePush::StartChange_U(float MaxU)
{
	bMoveUActive = true;
	MaxLocationU = MaxU;

	float ChangeLocation = FMath::FRandRange(LocationU - MaxOffset, LocationU + MaxOffset);
	float NewLocation = FMath::Clamp(ChangeLocation, 100.f, MaxLocationU);

	StartValue_U = LocationU;
	TargetValue_U = NewLocation;

	ChangeDuration_U = FMath::FRandRange(0.7f, 3.0f);
	ElapsedTime_U = 0.f;
}


void ALB_ObstaclePush::StartChange_V(float MaxV)
{
	bMoveVActive = true;
	MaxLocationV = MaxV;

	float ChangeLocation = FMath::FRandRange(LocationV - MaxOffset, LocationV + MaxOffset);
	float NewLocation = FMath::Clamp(ChangeLocation, 100.f, MaxLocationV);

	StartValue_V = LocationV;
	TargetValue_V = NewLocation;

	ChangeDuration_V = FMath::FRandRange(0.7f, 3.0f);
	ElapsedTime_V = 0.f;
}

void ALB_ObstaclePush::StopMovingTimer()
{
	bMoveUActive = false;
	bMoveVActive = false;
}

float ALB_ObstaclePush::GetRemainingTime() const
{
	if (!bMiniGameActive)
		return TimeUpTime;

	float Remaining = TimeUpTime - MiniGameElapsed;
	return FMath::Clamp(Remaining, 0.f, TimeUpTime);
}

bool ALB_ObstaclePush::IsWarningTime() const
{
	return GetRemainingTime() <= 5.f;
}
