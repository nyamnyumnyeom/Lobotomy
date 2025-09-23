#include "LB_GM.h"
#include "Character/LB_PlayerController.h"
#include "Character/LB_Character.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"
#include "NPC/LB_Monster_ChainSawMan.h"

ALB_GM::ALB_GM()
{
    DefaultPawnClass = ALB_Character::StaticClass();
    PlayerControllerClass = ALB_PlayerController::StaticClass();
}

void ALB_GM::BeginPlay()
{
    Super::BeginPlay();
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
