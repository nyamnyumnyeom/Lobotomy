// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/Ticker.h"
#include "LB_StoveSubsystem.generated.h"

namespace Stove
{
	namespace PCSDK
	{
		struct CallbackResult;

		namespace Base
		{
			struct StovePCInitializeParam;
		}

		namespace Ownership
		{
			struct StovePCOwnership;
		}
	}
}

/**
 * Stove PC SDK 3 Integration Subsystem
 */
UCLASS()
class LOBOTOMY_API ULB_StoveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	ULB_StoveSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	// Periodic tick function for running SDK callbacks
	bool Tick(float DeltaTime);

	// Internal helper handlers for callbacks
	void OnRestartAppIfNecessaryFinished(Stove::PCSDK::CallbackResult callbackResult, bool bRestartAppIfNecessary);
	void OnBaseSDKInitialized(Stove::PCSDK::CallbackResult callbackResult);
	void OnOwnershipListReceived(Stove::PCSDK::CallbackResult callbackResult, Stove::PCSDK::Ownership::StovePCOwnership* ownerships, uint32_t ownershipSize);

	// Tick delegate handle for FTSTicker
	FTSTicker::FDelegateHandle TickDelegateHandle;

	// State tracking flags
	bool bBaseSDKInitialized = false;
	bool bOwnershipSDKInitialized = false;

	// SDK init parameters stored as member to remain valid across async callbacks
	Stove::PCSDK::Base::StovePCInitializeParam* InitParamPtr = nullptr;
};
