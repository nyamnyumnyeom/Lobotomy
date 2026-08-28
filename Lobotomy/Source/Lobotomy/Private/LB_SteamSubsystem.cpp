#include "LB_SteamSubsystem.h"
#include "Misc/MessageDialog.h"
#include "HAL/PlatformMisc.h"

#undef min
#undef max

// 스팀 AppID 설정
const uint32 LOBOTOMY_STEAM_APPID = 4962770; // 사용자 설정의 AppID

ULB_SteamSubsystem::ULB_SteamSubsystem()
{
}

void ULB_SteamSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UE_LOG(LogTemp, Log, TEXT("ULB_SteamSubsystem::Initialize - Starting Steam Verification"));

#if !UE_EDITOR
    // 1. Steam 클라이언트를 통해 앱이 실행되었는지 확인 (DRM 기본 검사)
    // 잘못된 경로로 다이렉트 실행 시 기존 프로세스를 종료하고 스팀 클라이언트를 통해 게임을 다시 실행시킵니다.
    if (SteamAPI_RestartAppIfNecessary(LOBOTOMY_STEAM_APPID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Game not launched via Steam client. Relaunching through Steam..."));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }
#endif

    // 2. Steamworks API 초기화 확인
    if (!SteamAPI_Init())
    {
        UE_LOG(LogTemp, Error, TEXT("SteamAPI_Init() failed. Steam Client is not running."));
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Steam 클라이언트가 실행 중이 아닙니다. 게임을 종료합니다.")));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    // Tick 루프 등록 (비동기 콜백 수신용)
    TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateUObject(this, &ULB_SteamSubsystem::Tick),
        0.1f // 100ms 마다 실행
    );

    // 3. Encrypted App Ticket 요청
    UE_LOG(LogTemp, Log, TEXT("Requesting Encrypted App Ticket from Steam..."));
    SteamAPICall_t hAPICall = SteamUser()->RequestEncryptedAppTicket(nullptr, 0);
    EncryptedAppTicketCallResult.Set(hAPICall, this, &ULB_SteamSubsystem::OnEncryptedAppTicketResponse);
}

void ULB_SteamSubsystem::Deinitialize()
{
    if (TickDelegateHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
        TickDelegateHandle.Reset();
    }

    SteamAPI_Shutdown();
    Super::Deinitialize();
}

bool ULB_SteamSubsystem::Tick(float DeltaTime)
{
    SteamAPI_RunCallbacks();
    return true;
}

void ULB_SteamSubsystem::OnEncryptedAppTicketResponse(EncryptedAppTicketResponse_t* pResponse, bool bIOFailure)
{
    if (bIOFailure)
    {
        UE_LOG(LogTemp, Error, TEXT("EncryptedAppTicket IO Failure."));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    if (pResponse->m_eResult != k_EResultOK)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get EncryptedAppTicket from Steam. Result Code: %d"), (int)pResponse->m_eResult);
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("정품 인증 서버 연동 실패. 스팀 연결 상태를 확인해주세요.")));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    // 암호화된 티켓 가져오기
    uint8 rgubTicketEncrypted[1024];
    uint32 cubTicketEncrypted = 0;
    
    if (SteamUser()->GetEncryptedAppTicket(rgubTicketEncrypted, sizeof(rgubTicketEncrypted), &cubTicketEncrypted))
    {
		// 소유권 검증을 로컬로 돌리기 위한 함수.
		// 로컬 방식은 제대로 작동하지 않는 것 같아서 주석처리.
        //VerifyOwnership(rgubTicketEncrypted, cubTicketEncrypted);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GetEncryptedAppTicket returned false."));
        FGenericPlatformMisc::RequestExit(false);
    }
}

void ULB_SteamSubsystem::VerifyOwnership(uint8* pTicketEncrypted, uint32 cubTicketEncrypted)
{
    // 스팀웍스 대시보드에서 발급받은 32바이트 대칭키 기입 (실제 키로 교체 필요)
    // 예시 형식: 790e5dd3d42637... (총 32바이트 배열 구성)
    static const uint8 rgubKey[32] = {
        0xdd, 0x29, 0x8d, 0xb9, 0x6c, 0x5e, 0xc1, 0x8e,
        0x2f, 0xfd, 0x2f, 0x50, 0x69, 0x0a, 0x17, 0x04,
        0xb6, 0x3d, 0x40, 0x25, 0xe9, 0xe0, 0xec, 0x6c,
        0xc8, 0x20, 0xaa, 0x80, 0x96, 0x95, 0xea, 0xc5
    };

    uint8 rgubTicketDecrypted[1024];
    uint32 cubTicketDecrypted = sizeof(rgubTicketDecrypted);

    // 티켓 로컬 복호화 시도
    if (!SteamEncryptedAppTicket_BDecryptTicket(
            pTicketEncrypted, cubTicketEncrypted,
            rgubTicketDecrypted, &cubTicketDecrypted,
            rgubKey, sizeof(rgubKey)))
    {
        UE_LOG(LogTemp, Error, TEXT("Steam Ticket Decryption Failed. The key might be invalid."));
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("라이선스 인증 실패 (오류 코드: DEC_ERR). 정품 여부를 확인하세요.")));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    // 1. 티켓의 대상 AppID 검증
    if (!SteamEncryptedAppTicket_BIsTicketForApp(rgubTicketDecrypted, cubTicketDecrypted, LOBOTOMY_STEAM_APPID))
    {
        UE_LOG(LogTemp, Error, TEXT("Ticket AppID mismatch."));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    // 2. 해당 유저가 본 AppID를 소유하고 있는지 검증
    if (!SteamEncryptedAppTicket_BUserOwnsAppInTicket(rgubTicketDecrypted, cubTicketDecrypted, LOBOTOMY_STEAM_APPID))
    {
        UE_LOG(LogTemp, Warning, TEXT("User does not own the app according to ticket."));
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("이 계정은 게임 소유권을 가지고 있지 않습니다.")));
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    // 검증 성공
    UE_LOG(LogTemp, Log, TEXT("Steam Ownership Verification Success! Welcome to Lobotomy."));
}
