// Fill out your copyright notice in the Description page of Project Settings.

#include "LB_StoveSubsystem.h"
#include "BaseSDK.h"
#include "OwnershipSDK.h"
//#include "Lobotomy/StoveSignatureVerifier.h"

#undef min
#undef max

// Unreal logging category definition
DEFINE_LOG_CATEGORY_STATIC(LogStoveSDK, Log, All);

// Global static pointer to the active subsystem instance for callbacks
static ULB_StoveSubsystem* StoveSubsystemInstance = nullptr;

//ULB_StoveSubsystem::ULB_StoveSubsystem()
//{
//#if !UE_EDITOR
//	// 프로그램 시작(서브시스템 생성) 시점에 DLL 변조 여부 보안 검증 수행
//	StartStoveVerify();
//#endif
//}

void ULB_StoveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UE_LOG(LogStoveSDK, Log, TEXT("ULB_StoveSubsystem::Initialize - Starting Stove PCSDK3 integration"));

	StoveSubsystemInstance = this;

	// Allocate on heap so the pointer remains valid in async callbacks
	InitParamPtr = new Stove::PCSDK::Base::StovePCInitializeParam();
	InitParamPtr->SetEnvironment(L"LIVE");
	InitParamPtr->SetGameID(L"GM-27B4-69E1D8AC_IND");
	InitParamPtr->SetApplicationKey(L"790e5dd3d42637f66267b6b56258483add1c4d6e5243a77516a24663e18f6a25");

	// Register the ticker loop to execute SDK callbacks periodically.
	// Since Stove SDK callbacks are queued and processed asynchronously, 
	// we must call Base_RunCallback() on the main thread ticker.
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &ULB_StoveSubsystem::Tick),
		0.1f // Tick every 100ms
	);

#if UE_EDITOR
	// In the editor, skip the launcher check and initialize Base SDK directly
	UE_LOG(LogStoveSDK, Log, TEXT("Editor build: Skipping launcher check, calling Base_Initialize directly."));
	Stove::PCSDK::Base::Base_Initialize(InitParamPtr, [](Stove::PCSDK::CallbackResult callbackResult)
	{
		if (StoveSubsystemInstance)
		{
			StoveSubsystemInstance->OnBaseSDKInitialized(callbackResult);
		}
	});
#else
	// In packaged builds, verify the game was launched from the Stove Launcher first.
	// Base_Initialize must only be called after this check passes.
	UE_LOG(LogStoveSDK, Log, TEXT("Packaged build: Checking launcher connection via Base_RestartAppIfNecessaryAsync..."));
	Stove::PCSDK::Base::Base_RestartAppIfNecessaryAsync(
		InitParamPtr,
		5000, // 5-second timeout to wait for launcher IPC
		[](Stove::PCSDK::CallbackResult callbackResult, bool restartAppIfNecessary)
		{
			if (StoveSubsystemInstance)
			{
				StoveSubsystemInstance->OnRestartAppIfNecessaryFinished(callbackResult, restartAppIfNecessary);
			}
		}
	);
#endif
}

void ULB_StoveSubsystem::Deinitialize()
{
	UE_LOG(LogStoveSDK, Log, TEXT("ULB_StoveSubsystem::Deinitialize - Cleaning up Stove PCSDK3"));

	// Unregister ticker
	if (TickDelegateHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
		TickDelegateHandle.Reset();
	}

	// Uninitialize Ownership SDK first if it was initialized
	if (bOwnershipSDKInitialized)
	{
		Stove::PCSDK::Result OwnershipResult = Stove::PCSDK::Ownership::Ownership_UnInitialize();
		if (OwnershipResult.IsSuccessful())
		{
			UE_LOG(LogStoveSDK, Log, TEXT("Stove Ownership SDK uninitialized successfully"));
		}
		else
		{
			UE_LOG(LogStoveSDK, Warning, TEXT("Failed to uninitialize Stove Ownership SDK. ResultCode: %u"), OwnershipResult.GetResultCode());
		}
		bOwnershipSDKInitialized = false;
	}

	// Uninitialize Base SDK
	if (bBaseSDKInitialized)
	{
		Stove::PCSDK::Result BaseResult = Stove::PCSDK::Base::Base_UnInitialize();
		if (BaseResult.IsSuccessful())
		{
			UE_LOG(LogStoveSDK, Log, TEXT("Stove Base SDK uninitialized successfully"));
		}
		else
		{
			UE_LOG(LogStoveSDK, Warning, TEXT("Failed to uninitialize Stove Base SDK. ResultCode: %u"), BaseResult.GetResultCode());
		}
		bBaseSDKInitialized = false;
	}

	// Free the heap-allocated init params
	if (InitParamPtr)
	{
		delete InitParamPtr;
		InitParamPtr = nullptr;
	}

	if (StoveSubsystemInstance == this)
	{
		StoveSubsystemInstance = nullptr;
	}

	Super::Deinitialize();
}

bool ULB_StoveSubsystem::Tick(float DeltaTime)
{
	// Process queued callbacks (must run from the start to execute the initialization callback itself)
	Stove::PCSDK::Base::Base_RunCallback();
	return true; // Keep ticking
}

void ULB_StoveSubsystem::OnRestartAppIfNecessaryFinished(Stove::PCSDK::CallbackResult callbackResult, bool bRestartAppIfNecessary)
{
	if (!callbackResult.GetResult().IsSuccessful())
	{
		UE_LOG(LogStoveSDK, Error, TEXT("Base_RestartAppIfNecessaryAsync failed. ErrorMessage: %s, ExternalError: %d"),
			callbackResult.GetErrorMessage(),
			callbackResult.GetExternalError());
		FGenericPlatformMisc::RequestExit(false);
		return;
	}

	if (bRestartAppIfNecessary)
	{
		// Game was NOT launched via Stove Launcher — SDK will restart it through the launcher.
		// The process will exit and relaunch automatically; no further action needed here.
		UE_LOG(LogStoveSDK, Warning, TEXT("Game was not launched from Stove Launcher. Restarting through launcher..."));
		FGenericPlatformMisc::RequestExit(false);
		return;
	}

	// Game was launched from the launcher correctly — proceed with Base SDK initialization.
	UE_LOG(LogStoveSDK, Log, TEXT("Launcher connection verified. Calling Base_Initialize..."));
	Stove::PCSDK::Base::Base_Initialize(InitParamPtr, [](Stove::PCSDK::CallbackResult cbResult)
	{
		if (StoveSubsystemInstance)
		{
			StoveSubsystemInstance->OnBaseSDKInitialized(cbResult);
		}
	});
}

void ULB_StoveSubsystem::OnBaseSDKInitialized(Stove::PCSDK::CallbackResult callbackResult)
{
	if (callbackResult.GetResult().IsSuccessful())
	{
		UE_LOG(LogStoveSDK, Log, TEXT("Stove Base SDK Initialized Successfully."));
		bBaseSDKInitialized = true;

		// Once Base SDK is initialized, initialize Ownership SDK
		UE_LOG(LogStoveSDK, Log, TEXT("Initializing Stove Ownership SDK..."));
		Stove::PCSDK::Result OwnershipResult = Stove::PCSDK::Ownership::Ownership_Initialize();
		if (OwnershipResult.IsSuccessful())
		{
			UE_LOG(LogStoveSDK, Log, TEXT("Stove Ownership SDK Initialized."));
			bOwnershipSDKInitialized = true;

			// Request the list of ownerships for the game
			UE_LOG(LogStoveSDK, Log, TEXT("Requesting Stove Ownership list..."));
			Stove::PCSDK::Ownership::Ownership_OwnershipList([](
				Stove::PCSDK::CallbackResult cbResult, 
				Stove::PCSDK::Ownership::StovePCOwnership* ownerships, 
				uint32_t size)
			{
				if (StoveSubsystemInstance)
				{
					StoveSubsystemInstance->OnOwnershipListReceived(cbResult, ownerships, size);
				}
			});
		}
		else
		{
			UE_LOG(LogStoveSDK, Error, TEXT("Failed to initialize Stove Ownership SDK. ResultCode: %u"), OwnershipResult.GetResultCode());
		}
	}
	else
	{
		UE_LOG(LogStoveSDK, Error, TEXT("Failed to initialize Stove Base SDK. ErrorMessage: %s, ExternalError: %d"), 
			callbackResult.GetErrorMessage(), 
			callbackResult.GetExternalError());
	}
}

void ULB_StoveSubsystem::OnOwnershipListReceived(
	Stove::PCSDK::CallbackResult callbackResult, 
	Stove::PCSDK::Ownership::StovePCOwnership* ownerships, 
	uint32_t ownershipSize)
{
	if (callbackResult.GetResult().IsSuccessful())
	{
		UE_LOG(LogStoveSDK, Log, TEXT("Stove Ownership list retrieved successfully. Count: %u"), ownershipSize);

		bool bHasOwnership = false;

		for (uint32_t i = 0; i < ownershipSize; ++i)
		{
			Stove::PCSDK::Ownership::StovePCOwnership& Item = ownerships[i];
			
			UE_LOG(LogStoveSDK, Log, TEXT("Ownership Item - GameId: %s, GameCode: %d, OwnershipCode: %d"), 
				Item.GetGameId(), 
				static_cast<int>(Item.GetGameCode()), 
				static_cast<int>(Item.GetOwnershipCode()));

			if (Item.GetOwnershipCode() == Stove::PCSDK::Ownership::OwnershipCode::ACQUIRE)
			{
				if (wcscmp(L"GM-27B4-69E1D8AC_IND", Item.GetGameId()) == 0)
				{
					if (Item.GetGameCode() == Stove::PCSDK::Ownership::OwnershipGameCode::BASIC ||
						Item.GetGameCode() == Stove::PCSDK::Ownership::OwnershipGameCode::DEMO ||
						Item.GetGameCode() == Stove::PCSDK::Ownership::OwnershipGameCode::DLC)
					{
						bHasOwnership = true;
					}
				}
			}
		}

		if (bHasOwnership)
		{
			UE_LOG(LogStoveSDK, Log, TEXT("Stove Ownership Verified: User owns the game."));
		}
		else
		{
			UE_LOG(LogStoveSDK, Warning, TEXT("Stove Ownership Check Failed: User does not own the game."));
			FGenericPlatformMisc::RequestExit(false);
		}
	}
	else
	{
		UE_LOG(LogStoveSDK, Error, TEXT("Failed to retrieve Stove Ownership list. ErrorMessage: %s, ExternalError: %d"), 
			callbackResult.GetErrorMessage(), 
			callbackResult.GetExternalError());
	}
}
