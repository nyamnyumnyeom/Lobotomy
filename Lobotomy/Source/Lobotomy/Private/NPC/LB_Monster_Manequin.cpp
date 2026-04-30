// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_Monster_Manequin.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NPC/AI/LB_AICMonster_Manequin.h"
#include "Sound/SoundCue.h"
#include "LB_GM.h"

ALB_Monster_Manequin::ALB_Monster_Manequin()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Manequin"));
}

void ALB_Monster_Manequin::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(PlayerResistTimerHandle, this, &ALB_Monster_Manequin::Resist_PlayerCharacter_C, 1.0f, false);
		GetWorldTimerManager().SetTimer(OwnerAICResistTimerHandle, this, &ALB_Monster_Manequin::Resist_OwnerAIC, 1.0f, false);
	}

	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->SetManequinRef(this);
	}
}

void ALB_Monster_Manequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsAwake) return;

	if (IsPlayerLookingAtMe())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Player look at me!"));

		Manequin_StopLogic();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Where are you eyes on?"));

		Manequin_MoveLogic();
	}

	Reset_Apply();
}

void ALB_Monster_Manequin::Manequin_Awake()
{
	if (bIsAwake) return;

	bIsAwake = true;

	SetManequinResetLogic();
}

bool ALB_Monster_Manequin::IsPlayerLookingAtMe(float Threshold)
{
	if (!IsValid(PlayerCharacterReference_C)) return false;

	FVector PlayerForward = PlayerCharacterReference_C->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (GetActorLocation() - PlayerCharacterReference_C->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	if (Dot <= Threshold) return false;

	FVector Start = PlayerCharacterReference_C->GetActorLocation() + FVector(0.0f, 0.0f, 45.0f);
	TArray<FVector> EndPoints;

	EndPoints.Add(GetActorLocation());
	EndPoints.Add(GetActorLocation() + GetActorRightVector() * 30.0f);
	EndPoints.Add(GetActorLocation() - GetActorRightVector() * 30.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(PlayerCharacterReference_C);

	for (const FVector& End : EndPoints)
	{
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility,
			Params
		);

		if (!bHit)
		{
			if (GetWorld())
			{
				GetWorldTimerManager().ClearTimer(MoveRestartTimerHandle);
				bCanMoveRestartTimer = true;
			}

			return true;
		}
	}

	if (bCanMoveRestartTimer)
	{
		if (GetWorld())
		{
			bCanMoveRestartTimer = false;

			float MoveRestartTime = FMath::FRandRange(MoveRestartTime_Min, MoveRestartTime_Max);
			GetWorldTimerManager().SetTimer(MoveRestartTimerHandle, this, &ALB_Monster_Manequin::Manequin_Move_Restart, MoveRestartTime, false);
		}
	}

	return false;
}

void ALB_Monster_Manequin::Resist_PlayerCharacter_C()
{
	PlayerCharacterReference_C = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (IsValid(PlayerCharacterReference_C)) return;

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(PlayerResistTimerHandle, this, &ALB_Monster_Manequin::Resist_PlayerCharacter_C, 1.0f, false);
	}
}

void ALB_Monster_Manequin::Resist_OwnerAIC()
{
	OwnerAICReference = Cast<ALB_AICMonster_Manequin>(GetController());

	if (IsValid(OwnerAICReference)) return;

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(PlayerResistTimerHandle, this, &ALB_Monster_Manequin::Resist_OwnerAIC, 1.0f, false);
	}
}

void ALB_Monster_Manequin::SetRandomPose()
{
	if (!bCanPoseChangeTimer) return;

	bCanPoseChangeTimer = false;
	
	Pose_Index = FMath::RandRange(0, NumOfPose);

	PoseChange(Pose_Index);

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(PoseChangeTimerHandle, this, &ALB_Monster_Manequin::RandomPose_Restart, 5.0f, false);
	}
}

void ALB_Monster_Manequin::RandomPose_Restart()
{
	bCanPoseChangeTimer = true;
}

void ALB_Monster_Manequin::SetManequinResetLogic()
{
	float ResetTime = FMath::FRandRange(Manequin_ResetTime_Min, Manequin_ResetTime_Max);

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(ManequinRestartTimerHandle, this, &ALB_Monster_Manequin::ManequinReset, ResetTime, false);
	}
}

void ALB_Monster_Manequin::ManequinReset()
{
	bShouldReset = true;
}

void ALB_Monster_Manequin::Reset_Apply()
{
	if (bShouldReset == true && bIsPlayerEyesOnMe == false)
	{
		FVector LocationBeforeTeleport = GetActorLocation();

		if (TeleportToRandomNavLocation())
		{
			PlaySound_Manequin(SoundCue_Disappear, LocationBeforeTeleport);

			Manequin_StopLogic();

			OwnerAICReference->SetState_Idle();

			bIsMeetSound_Played = false;
			bShouldReset = false;
			bIsAwake = false;

			//OwnerAICReference->ResetBehaviorTree();
		}
	}
}

bool ALB_Monster_Manequin::TeleportToRandomNavLocation(float MinDistanceFromPlayer, float SearchRadius, int32 MaxAttempts)
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!NavSystem || !PlayerCharacter)
	{
		return false;
	}

	if (IsVisibleTime())
	{
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FNavLocation RandomLocation;

		for (int32 i = 0; i < MaxAttempts; ++i)
		{
			bool bFound = NavSystem->GetRandomReachablePointInRadius(GetActorLocation(), SearchRadius, RandomLocation);

			if (bFound)
			{
				if (FVector::Dist(RandomLocation.Location, PlayerLocation) > MinDistanceFromPlayer)
				{
					bool bSuccess = TeleportTo(RandomLocation.Location, GetActorRotation());
					if (bSuccess)
					{
						return true;
					}
				}
			}
		}
	}
	else
	{
		bool bSuccess = TeleportTo(FVector(4960.000004f, 2657.047936f, 14000.570533f), GetActorRotation());
		if (bSuccess)
		{
			return true;
		}
	}

	return false;
}

bool ALB_Monster_Manequin::IsVisibleTime()
{
	// 시간대를 받아와서 보이는 시간대인지 판단 후
	// TeleportToRandomNavLocation 함수 작동시
	// 레벨 내 유효한 위치에 이동시킬지, 이세계로 보낼지 판단해야댐.

	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return false;

	if (GM->bIsNight == false) return false;

	return true;
}

void ALB_Monster_Manequin::Manequin_MoveLogic()
{
	if (!bIsPlayerEyesOnMe) return;

	bIsPlayerEyesOnMe = false;

	if (IsValid(OwnerAICReference))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Move"));
		OwnerAICReference->MoveToPlayerBackward(true);

		SetRandomPose();
	}
}

void ALB_Monster_Manequin::Manequin_StopLogic()
{
	if (bIsPlayerEyesOnMe) return;

	bIsPlayerEyesOnMe = true;

	if (bIsMeetSound_Played == false)
	{
		PlaySound_Manequin(SoundCue_Meet, GetActorLocation());
		bIsMeetSound_Played = true;
	}

	if (IsValid(OwnerAICReference))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Stop"));
		OwnerAICReference->MoveToPlayerBackward(false);
	}
}

void ALB_Monster_Manequin::Manequin_Move_Restart()
{
	bIsPlayerEyesOnMe = true;
	bCanMoveRestartTimer = true;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Timer work"));
}

void ALB_Monster_Manequin::PlaySound_Manequin(USoundCue* Sound, FVector SoundLocation)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			Sound,
			SoundLocation
		);
	}

	Sanity_Reduces(0.5f);
}
