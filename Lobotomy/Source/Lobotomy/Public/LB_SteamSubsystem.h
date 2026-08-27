// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/Ticker.h"

// Steamworks SDK 헤더 포함 (컴파일러 경고 제어)
#pragma warning(push)
#pragma warning(disable: 4996)
#include "steam/steam_api.h"
#include "steamencryptedappticket.h"
#pragma warning(pop)

#include "LB_SteamSubsystem.generated.h"

/**
 * Steamworks SDK Integration & Ownership Verification Subsystem
 */
UCLASS()
class LOBOTOMY_API ULB_SteamSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

//public:
//	ULB_SteamSubsystem();
//
//	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
//	virtual void Deinitialize() override;
//
//private:
//	// 스팀 SDK 콜백 처리를 위한 주기적 틱 함수
//	bool Tick(float DeltaTime);
//
//	// 스팀 Encrypted App Ticket 요청 결과 콜백 핸들러
//	void OnEncryptedAppTicketResponse(EncryptedAppTicketResponse_t* pResponse, bool bIOFailure);
//
//	// 정품 소유권 검증 핵심 함수
//	void VerifyOwnership(uint8* pTicketEncrypted, uint32 cubTicketEncrypted);
//
//	// 틱 델리게이트 핸들
//	FTSTicker::FDelegateHandle TickDelegateHandle;
//
//	// 비동기 스팀 API 콜 결과를 바인딩하는 CallResult 객체
//	CCallResult<ULB_SteamSubsystem, EncryptedAppTicketResponse_t> EncryptedAppTicketCallResult;
};
