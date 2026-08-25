// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/LB_TargetPoint_MusicBox.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/LB_MusicBox.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Character.h"
#include "AchievementSubsystem.h"
#include "LB_GM.h"

ALB_TargetPoint_MusicBox::ALB_TargetPoint_MusicBox()
{
	PrimaryActorTick.bCanEverTick = false;

	ChainSawManBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	ChainSawManBillboard->SetupAttachment(RootComponent);
	ChainSawManBillboard->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));

	ChainSawManSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ChainSawManSpawnPoint"));
	ChainSawManSpawnPoint->SetupAttachment(ChainSawManBillboard);

	Tags.Add(FName("MusicBoxPoint"));
}

void ALB_TargetPoint_MusicBox::BeginPlay()
{
	Super::BeginPlay();

}

void ALB_TargetPoint_MusicBox::MusicBoxSystemActivate()
{
	if (SpawnedMusicBox != nullptr) return;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	FVector Start = SpawnLocation;
	FVector End = Start - FVector(0, 0, 100.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		SpawnLocation = HitResult.ImpactPoint;
	}

	if (MusicBoxClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		SpawnedMusicBox = GetWorld()->SpawnActor<ALB_MusicBox>(MusicBoxClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (SpawnedMusicBox)
		{
			SpawnedMusicBox->SetOwner(this);

			ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GM)
			{
				GM->SetMusicBoxRef(SpawnedMusicBox);
			}

			// 스팀 업적용
			CurrentAchivementTime = 0;
			GetWorldTimerManager().SetTimer(AchiveTimerHandle, this, &ALB_TargetPoint_MusicBox::MusicBoxAchivementTimer, 1.0f, true);

			GetWorldTimerManager().SetTimer(MusicBoxTimerHandle, this, &ALB_TargetPoint_MusicBox::MusicBoxTimeup, TimeupTime, false);
			GetWorldTimerManager().SetTimer(MusicBoxStopTimerHandle, this, &ALB_TargetPoint_MusicBox::StopMusicBoxTimer, DespawnTime, false);
		}
	}
}

void ALB_TargetPoint_MusicBox::StopMusicBoxTimer()
{
	if (bCanAchivement)
	{
		if (UGameInstance* GameInstance = GetGameInstance())
		{
			UAchievementSubsystem* AchievementSub = GameInstance->GetSubsystem<UAchievementSubsystem>();
			if (AchievementSub)
			{
				// 스팀웍스 대시보드에 등록된 API 이름을 인자로 전달합니다.
				AchievementSub->UnlockAchievement(FName("Chainsawman_ACHIEVEMENT"));
			}
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(MusicBoxTimerHandle);

	GetWorld()->GetTimerManager().ClearTimer(MusicBoxDestroyTimerHandle);

	GetWorldTimerManager().SetTimer(MusicBoxDestroyTimerHandle, this, &ALB_TargetPoint_MusicBox::TryMusicBoxDestroy, 0.7f, true);
}

void ALB_TargetPoint_MusicBox::MusicBoxTimeup()
{
	if (ChainSawManClass && ChainSawManSpawnPoint)
    {
		ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			if (!GM->GetIsChainSawManSpawned())
			{
				FVector SpawnLocation = ChainSawManSpawnPoint->GetComponentLocation();
				FRotator SpawnRotation = ChainSawManSpawnPoint->GetComponentRotation();
				
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				ALB_Monster_ChainSawMan* CSM = GetWorld()->SpawnActor<ALB_Monster_ChainSawMan>(ChainSawManClass, SpawnLocation, SpawnRotation, SpawnParams);
			}
			else
			{
				FVector SpawnLocation = ChainSawManSpawnPoint->GetComponentLocation();
				FRotator SpawnRotation = ChainSawManSpawnPoint->GetComponentRotation();
				FVector SpawnScale = FVector(1.0f, 1.0f, 1.0f);

				FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, SpawnScale);

				GM->SetChainSawManTransform(SpawnTransform);
			}
		}
    }
}

void ALB_TargetPoint_MusicBox::TryMusicBoxDestroy()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector PlayerForward = PlayerCharacter->GetActorForwardVector().GetSafeNormal();

	FVector ToPlayer = (GetActorLocation() - PlayerCharacter->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(PlayerForward, ToPlayer);

	if (Dot >= 0) return;

	GetWorld()->GetTimerManager().ClearTimer(MusicBoxDestroyTimerHandle);

	if (SpawnedMusicBox)
	{
		ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			GM->SetMusicBoxRef(nullptr);
		}

		SpawnedMusicBox->Destroy();
	}
}

void ALB_TargetPoint_MusicBox::MusicBoxAchivementTimer()
{
	CurrentAchivementTime += 1;

	if (AchivementTime <= CurrentAchivementTime)
	{
		bCanAchivement = true;
	}
}

void ALB_TargetPoint_MusicBox::MusicBoxAchivement()
{

}
