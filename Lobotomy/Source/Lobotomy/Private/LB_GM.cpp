#include "LB_GM.h"
#include "Character/LB_PlayerController.h"
#include "Character/LB_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"
#include "NPC/LB_Monster_ChainSawMan.h"
#include "LB_Setting.h"
#include "UI/LB_DialogueUI.h"
#include "UI/LB_ChartData.h"
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
	LoadPage(CurrentPage);
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

void ALB_GM::PlayerIntoRoom()
{
	GetWorldTimerManager().ClearTimer(PlayerTimerHandle);

	GetWorldTimerManager().ClearTimer(AtRoomSecondTimerHandle);

	bIsPlayerInRoom = true;

	float SpawnDelay = FMath::FRandRange(RoomDurationForSpawnHAS_Min, RoomDurationForSpawnHAS_Max);

	AtRoomSecondForMusicBox = FMath::RandRange(RoomDurationForMusicBox_Min, RoomDurationForMusicBox_Max);

	GetWorldTimerManager().SetTimer(PlayerTimerHandle, this, &ALB_GM::OnStayTimeOut, SpawnDelay, false);

	GetWorldTimerManager().SetTimer(AtRoomSecondTimerHandle, this, &ALB_GM::AtRoomSecondTimer, 1.0f, true);
}

void ALB_GM::PlayerIntoLobby()
{
	GetWorldTimerManager().ClearTimer(PlayerTimerHandle);

	GetWorldTimerManager().ClearTimer(AtRoomSecondTimerHandle);

	if (bShouldMusicBoxSpawn)
	{
		OnMusicBoxSpawnTime();
	}

	AtRoomSecond = 0;
	bShouldMusicBoxSpawn = false;

	bIsPlayerInRoom = false;

	float SpawnDelay = FMath::FRandRange(LobbyDurationForSpawnHAS_Min, LobbyDurationForSpawnHAS_Max);

	GetWorldTimerManager().SetTimer(PlayerTimerHandle, this, &ALB_GM::OnStayTimeOut, SpawnDelay, false);
}

void ALB_GM::AtRoomSecondTimer()
{
	if (AtRoomSecond >= AtRoomSecondForMusicBox)
	{
		bShouldMusicBoxSpawn = true;
	}

	AtRoomSecond++;
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

void ALB_GM::StartTimeCount()
{
	GetWorldTimerManager().SetTimer(TimeUpdateTimerHandle, this, &ALB_GM::UpdateTimeByTimer, 1.f, true);
}

void ALB_GM::StopTimeCount()
{
	GetWorldTimerManager().ClearTimer(TimeUpdateTimerHandle);
}
void ALB_GM::UpdateTimeByTimer()
{
	// 게임 내 시간 초 단위 증가
	CurrentSecond += FMath::FloorToInt(TimeScale);

	// 초 -> 분 변환
	if (CurrentSecond >= 60)
	{
		CurrentMinute += CurrentSecond / 60;
		CurrentSecond = CurrentSecond % 60;
	}

	// 분 -> 시 변환
	if (CurrentMinute >= 60)
	{
		CurrentHour += CurrentMinute / 60;
		CurrentMinute = CurrentMinute % 60;
	}

	// 하루 순환
	if (CurrentHour >= 24)
		CurrentHour = CurrentHour % 24;

	UE_LOG(LogTemp, Log, TEXT("Game Time: %02d:%02d"), CurrentHour, CurrentMinute);
}

void ALB_GM::GetGameTime(int32& Hours, int32& Minutes) const
{
	Hours = CurrentHour;
	Minutes = CurrentMinute;
}

void ALB_GM::SetGameTime(int32 Hour, int32 Minute)
{
	CurrentHour = Hour % 24;
	CurrentMinute = Minute % 60;
	CurrentSecond = 0;
}

bool ALB_GM::EnsurePageInCache(int32 Page)
{
	if (RuntimeCharts.Contains(Page)) return true;
	if (!ChartDataTable) return false;

	const FString RowName = FString::Printf(TEXT("Page_%02d"), Page);
	if (const FChartData* Row = ChartDataTable->FindRow<FChartData>(FName(*RowName), TEXT("LB_GM")))
	{
		FChartData Copy = *Row;
		// 안전장치: 체크박스 크기 보정(필요시)
		if (Copy.DayChecks.Num() < 7) { Copy.DayChecks.SetNum(7, /*bAllowShrinking*/false); }
		Copy.PageNumber = Page; // 보정
		RuntimeCharts.Add(Page, Copy);
		return true;
	}
	return false;
}

void ALB_GM::SyncCurrentFromCacheAndBroadcast()
{
	if (FChartData* Found = RuntimeCharts.Find(CurrentPage))
	{
		CurrentChart = *Found; // 현재 페이지 스냅샷
		OnChartUpdated.Broadcast(CurrentPage); // UI에게 “다시 그려!” 신호 //계속 안그리면 삭제함 ㅅㄱ
	}
}

void ALB_GM::LoadPage(int32 NewPage)
{
	CurrentPage = FMath::Max(1, NewPage);
	if (!EnsurePageInCache(CurrentPage))
	{
		UE_LOG(LogTemp, Warning, TEXT("No DataTable row for Page %d"), CurrentPage);
		// 없으면 빈 값으로라도 캐시 생성(선택)
		FChartData Blank;
		Blank.PageNumber = CurrentPage;
		Blank.DayChecks.SetNum(7);
		RuntimeCharts.Add(CurrentPage, Blank);
	}
	SyncCurrentFromCacheAndBroadcast();
}

FChartData ALB_GM::GetChartCopy(int32 Page) const
{
	if (const FChartData* Found = RuntimeCharts.Find(Page))
		return *Found;

	// 캐시에 없고 DataTable만 있을 수 있으므로 DataTable 조회(읽기 전용)
	if (ChartDataTable)
	{
		const FString RowName = FString::Printf(TEXT("Page_%02d"), Page);
		if (const FChartData* Row = ChartDataTable->FindRow<FChartData>(FName(*RowName), TEXT("LB_GM")))
			return *Row;
	}
	FChartData Empty; Empty.PageNumber = Page; Empty.DayChecks.SetNum(7);
	return Empty;
}

// --------- 수정 API (다른 액터/블루프린트에서 호출) ----------
void ALB_GM::SetNameForPage(int32 Page, const FText& NewName)
{
	if (!EnsurePageInCache(Page)) return;
	RuntimeCharts[Page].Name = NewName;
	if (Page == CurrentPage) SyncCurrentFromCacheAndBroadcast();
}

void ALB_GM::SetSymptomForPage(int32 Page, const FText& NewSymptom)
{
	if (!EnsurePageInCache(Page)) return;
	RuntimeCharts[Page].Symptom = NewSymptom;
	if (Page == CurrentPage) SyncCurrentFromCacheAndBroadcast();
}

void ALB_GM::SetRemarkForPage(int32 Page, const FText& NewRemark)
{
	if (!EnsurePageInCache(Page)) return;
	RuntimeCharts[Page].Remark = NewRemark;
	if (Page == CurrentPage) SyncCurrentFromCacheAndBroadcast();
}

void ALB_GM::SetDayCheckForPage(int32 Page, int32 DayIndex, bool bChecked)
{
	if (!EnsurePageInCache(Page)) return;
	if (RuntimeCharts[Page].DayChecks.Num() < 7) RuntimeCharts[Page].DayChecks.SetNum(7);
	if (RuntimeCharts[Page].DayChecks.IsValidIndex(DayIndex))
	{
		RuntimeCharts[Page].DayChecks[DayIndex] = bChecked;
		if (Page == CurrentPage) SyncCurrentFromCacheAndBroadcast();
	}
}

void ALB_GM::StartDialogue(FName StartRow)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		ALB_Character* Player = Cast<ALB_Character>(PC->GetPawn());
		if (Player)
		{
			Player->HideHUDUI();
		}

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}

	if (DialogueWidgetClass && DialogueTable)
	{
		ULB_DialogueUI* DialogueUI = CreateWidget<ULB_DialogueUI>(GetWorld(), DialogueWidgetClass);
		if (DialogueUI)
		{
			DialogueUI->AddToViewport(10);
			DialogueUI->InitDialogue(DialogueTable, StartRow);
		}
	}
}