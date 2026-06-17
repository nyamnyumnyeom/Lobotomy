#pragma once

/**
* @mainpage   Stove PC SDK 3
* \korean
* @section intro 소개
* - 스토브 플랫폼은 게임 배포, 업데이트, 지표 관리를 포함한, 게임 출시의 모든 과정을 쉽게 처리할 수 있는 통합 서비스를 제공합니다.
    스토브 PC SDK를 사용하면 스토브 플랫폼이 제공하는 서비스를 게임에 쉽게 통합할 수 있습니다.
*
* @section SDK종류
* - BaseSDK : 스토브 플랫폼을 사용하기 위한 모든 기본적인 정보를 관리하는 모듈입니다 (필수).
* - GameSupportSDK : 게임 지원 서비스를 연동할 수 있는 모듈입니다.
* - GamingServicesSDK : 게임 서비스를 연동할 수 있는 모듈입니다.
* - IAPSDK : 빌링을 연동할 수 있는 모듈입니다.
* - OwnershipSDK : 게임의 소유권을 확인할 수 있는 모듈입니다.
* - ViewSDK : 팝업창을 연동할 수 있는 모듈입니다.
* - PCBangSDK : PC방 서비스를 연동할 수 있는 모듈입니다.
*
* @section SDK오류코드
* - BaseSDK의 오류 코드 페이지 \ref BaseSDK\Deploy\Include\Misc\BaseSDKResult.h
* - GameSupportSDK의 오류 코드 페이지 \ref GameSupportSDK\Deploy\Include\Misc\GameSupportSDKResult.h
* - GamingServicesSDK의 오류 코드 페이지 \ref GamingServicesSDK\Deploy\Include\Misc\GamingServicesSDKResult.h
* - IAPSDK의 오류 코드 페이지 \ref IAPSDK\Deploy\Include\Misc\IAPSDKResult.h
* - OwnershipSDK의 오류 코드 페이지 \ref OwnershipSDK\Deploy\Include\Misc\OwnershipSDKResult.h
* - PCBangSDK의 오류 코드 페이지 \ref PCBangSDK\Deploy\Include\Misc\PCBangSDKResult.h
* - ViewSDK의 오류 코드 페이지 \ref ViewSDK\Deploy\Include\Misc\ViewSDKResult.h
* \endkorean
* \english
* @section intro Introduction
* - The Stove platform provides an integrated service that makes it easy to handle all aspects of game release, including game distribution, updates, and metrics management.
    By using the Stove PC SDK, you can easily integrate the services provided by the Stove platform into your game.
*
* @section SDKTypes
* - BaseSDK: A module that manages all the basic information needed to use the Stove platform (required).
* - GameSupportSDK: A module that integrates game support services.
* - GamingServicesSDK: A module that integrates game services.
* - IAPSDK: A module that integrates billing.
* - OwnershipSDK: A module that verifies game ownership.
* - ViewSDK: A module that integrates pop-up windows.
* - PCBangSDK: A module that integrates PC bang services.
*
* @section SDKErrorCodes
* - Error code page for BaseSDK \ref BaseSDK\Deploy\Include\Misc\BaseSDKResult.h
* - Error code page for GameSupportSDK \ref GameSupportSDK\Deploy\Include\Misc\GameSupportSDKResult.h
* - Error code page for GamingServicesSDK \ref GamingServicesSDK\Deploy\Include\Misc\GamingServicesSDKResult.h
* - Error code page for IAPSDK \ref IAPSDK\Deploy\Include\Misc\IAPSDKResult.h
* - Error code page for OwnershipSDK \ref OwnershipSDK\Deploy\Include\Misc\OwnershipSDKResult.h
* - Error code page for PCBangSDK \ref PCBangSDK\Deploy\Include\Misc\PCBangSDKResult.h
* - Error code page for ViewSDK \ref ViewSDK\Deploy\Include\Misc\ViewSDKResult.h
* \endenglish
*/

/*!
    * @file     BaseSDK.h
    * \korean
    * @brief    BaseSDK에서 제공하는 함수의 헤더입니다.
    * \endkorean
    * \english
    * @brief    Header of the functions provided by BaseSDK.
    * \endenglish
*/

#include <string>

#include "Misc/BaseSDKCallbacks.h"
#include "Misc/BaseSDKEnumerations.h"
#include "Misc/BaseSDKStructures.h"
#include "Misc/BaseSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Base
        {
            /*!
            * \korean
            * @brief PCSDK가 런처를 통해 실행이 되었는지 확인합니다.
            * @details 런처가 실행이 되어 있지않거나 런처를 통해 프로그램이 실행이 되지 않았으면 스토브 프로토콜 핸들러를 이용하여 다시 실행합니다. (Synchronous)
            * @param[in] StovePCInitializeParam* initParam 초기화를 하기 위한 정보
            * \endkorean
            * \english
            * @brief Checks if the PCSDK is running through the launcher.
            * @details If the launcher is not running or the program is not running through the launcher, it will restart using the Stove protocol handler. (Synchronous)
            * @param[in] StovePCInitializeParam* initParam Information for initialization
            * \endenglish
            */
            bool Base_RestartAppIfNecessary(const StovePCInitializeParam* initParam);

            /*!
            * \korean
            * @brief PCSDK가 런처를 통해 실행이 되었는지 확인합니다.
            * @details 런처가 실행이 되어 있지않거나 런처를 통해 프로그램이 실행이 되지 않았으면 스토브 프로토콜 핸들러를 이용하여 다시 실행합니다. (Asynchronous)
            * @param[in] StovePCInitializeParam* initParam 초기화를 하기 위한 정보
            * @param[in] uint32_t waitTimeMillisec 런처를 통해 실행이 되었는지 확인을 기다리는 시간 (권장하는 값 60'000 == 1분)
            * @param[in] OnRestartAppIfNecessaryFinished onFinished 런처로 부터 실행되었는지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Checks if the PCSDK is running through the launcher.
            * @details If the launcher is not running or the program is not running through the launcher, it will restart using the Stove protocol handler. (Asynchronous)
            * @param[in] StovePCInitializeParam* initParam Information for initialization
            * @param[in] uint32_t waitTimeMillisec Time to wait for confirmation that the program is running through the launcher (recommended value 60'000 == 1 minute)
            * @param[in] OnRestartAppIfNecessaryAsyncFinished onFinished Callback function to receive the result of whether the program is running through the launcher
            * \endenglish
            */
            void Base_RestartAppIfNecessaryAsync(const StovePCInitializeParam* initParam, uint32_t waitTimeMillisec, OnRestartAppIfNecessaryAsyncFinished onFinished);

            /*!
            * @fn           void StoveAPI_RestartAppIfNecessaryAsyncEx(const StoveInitializeParam* initParam, uint32_t waitTimeMillisec, bool launchLauncher,       OnRestartAppIfNecessaryAsync onFinished, void* userData)
            * \korean
            * @brief        PCSDK가 런처를 통해 실행이 되었는지 확인합니다.
            * @details      런처가 실행이 되어 있지않거나 런처를 통해 프로그램이 실행이 되지 않았으면 스토브 프로토콜 핸들러를 이용하여 다시 실행합니다. (Asynchronous)
            * @param[in]    StoveInitializeParam* initParam 초기화를 하기 위한 정보
            * @param[in]    uint32_t waitTimeMillisec 런처를 통해 실행이 되었는지 확인을 기다리는 시간 (권장하는 값 60'000 == 1분)
            * @praam[in]    bool launchLauncher 런처를 통해 실행이 되지 않았을 때 런처를 실행할지 여부 (true: 런처 실행, false: 런처 실행 안함)
            * @param[in]    OnRestartAppIfNecessaryAsync onFinished 런처로 부터 실행되었는지에 대한 결과를 넘겨받는 Callback 함수
            * @param[in]    void* userData 콜백 호출 시 넘기는 사용자 데이터 (필수가 아니며, 넘긴 데이터는 사용자에게 다시 전달됩니다.)
            * \endkorean
            * \english
            * @brief        Check if the PCSDK is running through the launcher.
            * @details      If the launcher is not running or the program is not running through the launcher, it will be restarted using the Stove protocol    handler.   (Asynchronous)
            * @param[in]    StoveInitializeParam* initParam Information for initialization
            * @param[in]    uint32_t waitTimeMillisec Time to wait for confirmation of running through the launcher (recommended value 60'000 == 1 minute)
            * @param[in]    bool launchLauncher Whether to launch the launcher if it is not running through the launcher (true: launch the launcher, false: do not  launch   the launcher)
            * @param[in]    OnRestartAppIfNecessaryAsync onFinished Callback function to receive the result of whether it was executed through the launcher
            * @param[in]    void* userData User data passed when the callback is called (not required, and the passed data is passed back to the user.)
            * \endenglish
            */
            void Base_RestartAppIfNecessaryAsyncEx(const StovePCInitializeParam* initParam, uint32_t waitTimeMillisec, bool launchLauncher, OnRestartAppIfNecessaryAsyncFinished onFinished);

            /*!
            * \korean
            * @brief        PCSDK가 런처를 통해 실행이 되었는지 확인합니다.
            * @details      런처가 실행이 되어 있지않거나 런처를 통해 프로그램이 실행이 되지 않았으면 스토브 프로토콜 핸들러를 이용하여 다시 실행합니다. (Asynchronous)
            *               waitTimeMillisec과 launchLauncher 옵션은 StovePCInitializeParamEx2 구조체에 포함되어 있습니다.
            * @param[in]    StovePCInitializeParamEx2* initParam 초기화를 하기 위한 정보 (waitTimeMillisec과 launchLauncher 포함)
            * @param[in]    OnRestartAppIfNecessaryAsyncFinished onFinished 런처로 부터 실행되었는지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief        Check if the PCSDK is running through the launcher.
            * @details      If the launcher is not running or the program is not running through the launcher, it will be restarted using the Stove protocol handler. (Asynchronous)
            *               The waitTimeMillisec and launchLauncher options are included in the StovePCInitializeParamEx2 structure.
            * @param[in]    StovePCInitializeParamEx2* initParam Information for initialization (including waitTimeMillisec and launchLauncher)
            * @param[in]    OnRestartAppIfNecessaryAsyncFinished onFinished Callback function to receive the result of whether it was executed through the launcher
            * \endenglish
            */
            void Base_RestartAppIfNecessaryAsyncEx2(const StovePCInitializeParamEx2* initParam, OnRestartAppIfNecessaryAsyncFinished onFinished);

            /*!
            * \korean
            * @brief BaseSDK를 초기화 합니다.
            * @param[in] StovePCInitializeParam* initParam 초기화를 하기 위한 정보
            * @param[in] OnInitializeFinished onFinished 초기화에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Initializes the BaseSDK.
            * @param[in] StovePCInitializeParam* initParam Information for initialization
            * @param[in] OnInitializeFinished onFinished Callback function to receive the result of initialization
            * \endenglish
            */
            void Base_Initialize(const StovePCInitializeParam* initParam, OnInitializeFinished onFinished);

            /*!
            * \korean
            * @brief 캐시된 파라미터를 사용하여 BaseSDK를 초기화합니다.
            * @details Base_RestartAppIfNecessary 호출로 캐시된 초기화 파라미터를 재사용합니다.
            * @param[in] OnInitializeFinished onFinished 초기화에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Initializes the BaseSDK using cached parameters.
            * @details Reuses initialization parameters cached by Base_RestartAppIfNecessary call.
            * @param[in] OnInitializeFinished onFinished Callback function to receive the result of initialization
            * \endenglish
            */
            void Base_InitializeEx(OnInitializeFinished onFinished);

            /*!
            * \korean
            * @brief BaseSDK의 자원을 해제합니다
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Releases the resources of the BaseSDK
            * @return class Result function call result
            * \endenglish
            */
            Result Base_UnInitialize();

            /*!
            * \korean
            * @brief 각각의 SDK 모듈에서 등록한 Callback 함수를 실행합니다.
            * @details 등록된 콜백을 전부다 실행합니다
            * \endkorean
            * \english
            * @brief Executes the callback functions registered in each SDK module.
            * @details Executes all registered callbacks
            * \endenglish
            */
            void Base_RunCallback();

            /*!
            * \korean
            * @brief 각각의 SDK 모듈에서 등록한 Callback 함수를 실행합니다.
            * @details 등록된 콜백을 실행할 때 시간을 계산하여 timeoutMillisec을 초과하면 실행을 중지합니다.
            *          다음에 호출될 때 이어서 실행합니다.
            * @param[in] uint32_t timeoutMillisec 타임아웃 시간 (밀리초)
            * \endkorean
            * \english
            * @brief Executes the callback functions registered in each SDK module.
            * @details When executing the registered callback, calculate the time and stop the execution if it exceeds timeoutMillisec.
            *          It will continue to execute when called next.
            * @param[in] uint32_t timeoutMillisec Timeout time (milliseconds)
            * \endenglish
            */
            void Base_RunCallbackWithTimeout(uint32_t timeoutMillisec);

            /*!
            * \korean
            * @brief Stove에서 사용 가능한 AccessToken을 반환해줍니다
            * @param[out] wchar_t* accessToken 유효한 AccessToken을 조회합니다
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Returns the AccessToken that can be used in Stove
            * @param[out] wchar_t* accessToken Get a valid AccessToken
            * @param[in] uint32_t length Length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetAccessToken(__out wchar_t* accessToken, uint32_t length);

            /*!
            * \korean
            * @brief Stove에서 사용 가능한 AccessToken이 갱신되는 시점에 새로 발급된 AccessToken을 등록한 Callback 함수에 넘겨줍니다
            * @details 새로운 Access Token을 발급받는 함수가 아닙니다
            * @param[in] OnRenewTokenFinished onFinished 새로 발급된 AccessToken을 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the newly issued AccessToken to the Callback function registered when the AccessToken that can be used in Stove is renewed
            * @details This is not a function to get a new Access Token
            * @param[in] OnRenewTokenFinished onFinished Callback function to receive the newly issued AccessToken
            * \endenglish
            */
            void Base_AccessTokenRenewed(OnRenewTokenFinished onFinished);

            /*!
            * \korean
            * @brief Stove에서 사용 가능한 AccessToken이 갱신되는 시점에 새로 발급된 AccessToken을 등록한 Callback 함수에 넘겨줍니다
            * @details Deprecated 될 예정입니다 Base_AccessTokenRenewed를 대신 사용해주세요.
            * @param[in] OnRenewTokenFinished onFinished 새로 발급된 AccessToken을 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the newly issued AccessToken to the Callback function registered when the AccessToken that can be used in Stove is renewed
            * @details This is not a function to get a new Access Token
            * @param[in] OnRenewTokenFinished onFinished Callback function to receive the newly issued AccessToken
            * \endenglish
            */
            void Base_GetRenewToken(OnRenewTokenFinished onFinished);

            /*!
            * \korean
            * @brief User의 정보를 반환해줍니다
            * @param[out] StovePCUser* user 로그인한 사용자의 정보를 조회합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Returns the information of the User
            * @param[out] StovePCUser* user Get the information of the logged-in user
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetUser(__out StovePCUser* user);

            /*!
            * \korean
            * @brief GDS의 정보를 반환해줍니다
            * @param[out] StovePCGds* gds 로그인한 사용자의 국가 정보를 조회합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Returns the information of the GDS
            * @param[out] StovePCGds* gds Get the country information of the logged-in user
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetGds(__out StovePCGds* gds);

            /*!
            * \korean
            * @brief Signin의 정보를 반환해줍니다
            * @param[out] StovePCSignin* signin 로그인한 사용자의 서명 정보를 조회합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Returns the information of the Signin
            * @param[out] StovePCSignin* signin Get the signature information of the logged-in user
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetSignin(__out StovePCSignin* signin);

            /*!
            * \korean
            * @brief BaseSDK의 언어 정보를 설정합니다
            * @param[in] StoveLanguage language 언어 정보
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Sets the language information of the BaseSDK
            * @param[in] StoveLanguage language Language information
            * @return class Result function call result
            * \endenglish
            */
            Result Base_SetLanguage(StoveLanguage language);

            /*!
            * \korean
            * @brief PCSDK의 언어 정보를 설정합니다
            * @param[in] const wchar_t* language 언어 정보
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Sets the language information of the PCSDK
            * @param[in] const wchar_t* language Language information
            * @return class Result function call result
            * \endenglish
            */
            Result Base_SetLanguageEx(const wchar_t* language);

            /*!
            * \korean
            * @brief 한국 과몰입 방지 대상자에게 게임 플레이 1시간마다 정보를 등록한 Callback 함수에 넘겨줍니다
            * @note 한국 전용 API입니다.
            * @param[in] OnOverImmersionFinished onFinished 과몰입 방지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the Korea over-immersion prevention information to the Callback function registered every hour of gameplay
            * @note This API is for Korea only.
            * @param[in] OnOverImmersionFinished onFinished Callback function to receive the result of over-immersion prevention
            * \endenglish
            */
            void Base_OverImmersionNotification(OnOverImmersionFinished callback);

            /*!
            * \korean
            * @brief 한국 과몰입 방지 대상자에게 게임 플레이 1시간마다 정보를 등록한 Callback 함수에 넘겨줍니다
            * @note 한국 전용 API입니다.
            * @details Deprecated 될 예정입니다 Base_OverImmersionNotification를 대신 사용해주세요.
            * @param[in] OnOverImmersionFinished onFinished 과몰입 방지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the Korea over-immersion prevention information to the Callback function registered every hour of gameplay
            * @note This API is for Korea only.
            * @details This is deprecated. Please use Base_OverImmersionNotification instead.
            * @param[in] OnOverImmersionFinished onFinished Callback function to receive the result of over-immersion prevention
            * \endenglish
            */
            void Base_GetOverImmersion(OnOverImmersionFinished callback);

            /*!
            * \korean
            * @brief 셧다운 대상자이면 셧다운 알림을 등록한 Callback 함수에 넘겨줍니다
            * @param[in] OnShutdownFinished onFinished 셧다운 대상자인지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the shutdown notification to the Callback function registered if it is a shutdown target
            * @param[in] OnShutdownFinished onFinished Callback function to receive the result of whether it is a shutdown target
            * \endenglish
            */
            void Base_ShutdownNotification(OnShutdownFinished callback);

            /*!
            * \korean
            * @brief 셧다운 대상자이면 셧다운 알림을 등록한 Callback 함수에 넘겨줍니다
            * @details Deprecated 될 예정입니다 Base_ShutdownNotification를 대신 사용해주세요.
            * @param[in] OnShutdownFinished onFinished 셧다운 대상자인지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the shutdown notification to the Callback function registered if it is a shutdown target
            * @details This is deprecated. Please use Base_ShutdownNotification instead.
            * @param[in] OnShutdownFinished onFinished Callback function to receive the result of whether it is a shutdown target
            * \endenglish
            */
            void Base_GetShutdown(OnShutdownFinished callback);

            /*!
            * \korean
            * @brief 베트남 연령 등급 안내 오버레이 정보를 등록한 Callback 함수에 넘겨줍니다
            * @note 베트남 전용 API입니다. 타이머 없이 런처의 SHOW/HIDE 패킷으로만 동작합니다.
            * @param[in] OnVietnamAgeRatingFinished onFinished 베트남 연령 등급 안내에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the Vietnam age rating notification overlay information to the registered Callback function
            * @note This API is for Vietnam only. Operates only via SHOW/HIDE packets from launcher, without timer.
            * @param[in] OnVietnamAgeRatingFinished onFinished Callback function to receive the result of Vietnam age rating notification
            * \endenglish
            */
            void Base_VietnamAgeRatingNotification(OnVietnamAgeRatingFinished callback);

            /*!
            * \korean
            * @brief 베트남 과몰입 방지 대상자에게 게임 플레이 중 정기적으로 정보를 등록한 Callback 함수에 넘겨줍니다
            * @note 베트남 전용 API입니다.
            * @param[in] OnVietnamOverimmersionFinished onFinished 베트남 과몰입 방지에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Passes the Vietnam over-immersion prevention information to the Callback function registered periodically during gameplay
            * @note This API is for Vietnam only.
            * @param[in] OnVietnamOverimmersionFinished onFinished Callback function to receive the result of Vietnam over-immersion prevention
            * \endenglish
            */
            void Base_VietnamOverimmersionNotification(OnVietnamOverimmersionFinished callback);

            /*!
            * \korean
            * @brief 스토브 플랫폼 동선 추적을 위한 일련의 단서를 조회합니다
            * @param[out] StovePCTraceHint* traceHint 플랫폼 동선에 대한 정보
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Retrieves a series of clues for Stove platform tracking
            * @param[out] StovePCTraceHint* traceHint Information about the platform route
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetTraceHint(__out StovePCTraceHint* traceHint);

            /*!
            * \korean
            * @brief 게임프로필을 설정합니다.
            * @param[in] StovePCGameProfile* gameProfile 게임 프로필 정보
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Sets the game profile.
            * @param[in] StovePCGameProfile* gameProfile Game profile information
            * @return class Result function call result
            * \endenglish
            */
            Result Base_SetGameProfile(const StovePCGameProfile* gameProfile);


            /*!
            * \korean
            * @brief 외부 브라우저를 통해 URL을 엽니다. Stove 관련 도메인 오픈 시 SSO 처리를 진행합니다. (ex. Stove 커뮤니티, 고객센터)
            * @param[in] wchar_t* url 열고자 하는 URL
            * @param[in] OnOpenExternalUrlFinished onFinished OpenExternalUrl 실행에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Open the URL through an external browser. SSO processing is performed when opening Stove-related domains. (ex. Stove community, customer center)
            * @param[in] wchar_t* url URL to open
            * @param[in] OnOpenExternalUrlFinished onFinished Callback function to receive the result of OpenExternalUrl execution
            * \endenglish
            */
            void Base_OpenExternalUrl(const wchar_t* url, OnOpenExternalUrlFinished onFinished);

            /*!
            * \korean
            * @brief 클라우드 세이브 경로를 반환해줍니다
            * @param[out] wchar_t* cloudSavingPath 클라우드 세이브 경로 정보
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Returns the cloud saving path
            * @param[out] wchar_t* cloudSavingPath Cloud saving path information
            * @param[in] uint32_t length Length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetCloudSavingPath(__out wchar_t* cloudSavingPath, uint32_t length);

            /*!
            * \korean
            * @brief BaseSDK의 버전 정보를 조회합니다.
            * @param[out] wchar_t* version 버전 정보
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Retrieves the version information of the BaseSDK.
            * @param[out] wchar_t* version Version information
            * @param[in] uint32_t length Length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result Base_GetVersion(__out wchar_t* version, uint32_t length);
        }
    }
}