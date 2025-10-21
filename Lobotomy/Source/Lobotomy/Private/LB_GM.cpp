#include "LB_GM.h"
#include "Character/LB_PlayerController.h"
#include "Character/LB_Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"
#include "NPC/LB_Monster_ChainSawMan.h"
#include "LB_Setting.h"
#include "UI/LB_SettingUI.h"

ALB_GM::ALB_GM()
{
    DefaultPawnClass = ALB_Character::StaticClass();
    PlayerControllerClass = ALB_PlayerController::StaticClass();
}

void ALB_GM::BeginPlay()
{
    Super::BeginPlay();
	ULB_Setting* S = ULB_Setting::Get();
}

void ALB_GM::PlayerDeathLogic(FVector TargetLocation)
{
	ALB_Character* LB_Character = Cast<ALB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!LB_Character) return;

	LB_Character->PlayCameraDeathSequence(TargetLocation);
}

void ALB_GM::UpdateSet()
{
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		if (ULB_Setting* LBSetting = Cast<ULB_Setting>(Settings))
		{
			LBSetting->LoadSettings(true);
			LBSetting->ApplySettings(true);
			LBSetting->ApplyCustomSettings();
		}
	}
}

void ALB_GM::AddKnockCount()
{
	KnockCount++;

	if (KnockCount >= PatienceLimit)
	{
		ShouldChainSawManSpawn = FMath::RandBool();
	}
}

void ALB_GM::ResetKnockCount()
{
	KnockCount = 0;
	ShouldChainSawManSpawn = false;
}

void ALB_GM::SetChainSawManTransform(FTransform NewTransform)
{
	if (!ChainSawManRef.IsValid()) return;

	ALB_Monster_ChainSawMan* CurrentChainSawMan = Cast<ALB_Monster_ChainSawMan>(ChainSawManRef.Get());
	if (CurrentChainSawMan)
	{
		CurrentChainSawMan->SetActorTransform(NewTransform);
		CurrentChainSawMan->SpawnLogic();
	}
}

float ALB_GM::GetChainSawManToPlayerDistance()
{
	if (ChainSawManRef.IsValid())
	{
		FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		FVector ChainSawManLocation = ChainSawManRef->GetActorLocation();

		FHitResult Hit;
		FCollisionQueryParams Params;

		bool bBlocked = GetWorld()->LineTraceSingleByChannel(
			Hit,
			PlayerLocation,
			ChainSawManLocation,
			ECC_Visibility,
			Params
		);

		if (!bBlocked)
		{
			float Distance = FVector::Dist(PlayerLocation, ChainSawManLocation);

			return Distance;
		}
		else
		{
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
			if (NavSys)
			{
				UNavigationPath* Path = NavSys->FindPathToLocationSynchronously(GetWorld(), PlayerLocation, ChainSawManLocation);
				if (Path && Path->IsValid() && Path->PathPoints.Num() > 1)
				{
					float PathLen = 0.f;
					for (int32 i = 1; i < Path->PathPoints.Num(); i++)
					{
						PathLen += FVector::Dist(Path->PathPoints[i - 1], Path->PathPoints[i]);
					}
					return PathLen;
				}

				return -1.0f;
			}
		}
	}

	return -1.0f;
}

void ALB_GM::UpdateDate()
{
	CurrentDay++;
}

void ALB_GM::ClearDate()
{
	CurrentDay = 1;
}

void ALB_GM::ChangeToNight()
{
	bIsNight = true;
}

void ALB_GM::ChangeToDay()
{
	bIsNight = false;
	UpdateDate();
}