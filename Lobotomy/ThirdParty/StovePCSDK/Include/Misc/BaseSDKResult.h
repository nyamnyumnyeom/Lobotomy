#pragma once

/*!
    * @file     BaseSDKResult.h
    * \korean
    * @brief    BaseSDK에서 사용하는 Code값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of the Code value used in BaseSDK.
    * \endenglish
*/

#include "Result/Result.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Base
        {
            /*!
            * \korean
            * @brief    BaseSDK에서 사용하는 함수들의 Code
            * \endkorean
            * \english
            * @brief    Code of functions used in BaseSDK
            * \endenglish
            */
            enum class SDKMethod : uint32_t
            {
                /*
                * Common Method
                */
                /// 1 : Base_Initialize
                INITIALIZE = 1U,

                /// 2 : Base_UnInitialize
                UNINITIALIZE = 2U,

                /// 3 : Internal method
                INTERNAL_SEND_81PLUG = 3U,

                /// 4 : Internal method
                INTERNAL_UPDATE_81PLUG = 4U,

                /// 5 : Base_GetVersion
                GET_VERSION = 5U,

                /*
                * BaseSDK Method
                */
                /// 64 : Base_GetAccessToken
                GET_ACCESS_TOKEN = 64U,

                /// 65 : Base_AccessTokenRenewed
                ACCESS_TOKEN_RENEWED = 65U,

                /// 66 : Base_GetUser
                GET_USER = 66U,

                /// 67 : Base_SetLanguage
                SET_LANGUAGE = 67U,

                /// 68 : Base_OverImmersionNotification
                OVER_IMMERSION_NOTIFICATION = 68U,

                /// 69 : Base_ShutdownNotification
                SHUTDOWN_NOTIFICATION = 69U,

                /// 70 : Base_LogAdd (deprecated)
                LOG_ADD = 70U,

                /// 71 : Base_GetTraceHint
                GET_TRACE_HINT = 71U,

                /// 72 : Base_SetGameProfile
                SET_GAME_PROFILE = 72U,

                /// 73 : Base_GetGds
                GET_GDS = 73U,

                /// 74 : Base_Signin
                GET_SIGNIN = 74U,

                /// 75 : Base_RestartAppIfNecessary
                RESTART_APP_IF_NECESSARY = 75U,

                /// 76 : Base_RestartAppIfNecessaryAsync
                RESTART_APP_IF_NECESSARY_ASYNC = 76U,

                /// 77 : Base_OpenExternalUrl
                OPEN_EXTERNAL_URL = 77U,

                /// 78 : Base_GetCloudSavingPath
                GET_CLOUD_SAVING_PATH = 78U,

                /// 79 : Base_VietnamAgeRatingNotification
                VIETNAM_AGE_RATING_NOTIFICATION = 79U,

                /// 80 : Base_VietnamOverimmersionNotification
                VIETNAM_OVER_IMMERSION_NOTIFICATION = 80U,

                /// Internal method
                INTERNAL_SET_PLAYTIME_REPORT = 96U,

                /// Internal method
                INTERNAL_OPERATOR_REPORT_PLAYTIME = 97U,

                /// Internal method
                INTERNAL_GAME_EXIT_REPORT_PLAYTIME = 98U,

                /// Internal method
                INTERNAL_FILE_SAVE_UNSET_PLAYTIME = 99U,

                /// Internal method
                INTERNAL_FAILED_PLAYTIME_TRANSFERS = 100U,

                /// Internal method
                INTERNAL_OPERATOR_REPORT_CONCURRENT_USER = 101U,

                /// Internal method
                INTERNAL_SERVER_CONFIG = 102U,

                /// Internal method
                INTERNAL_GDS_INFO = 103U,

                /// Internal method
                INTERNAL_GAME_CHECKER_LOGIN = 104U,

                /// Internal method
                INTERNAL_ONSTOVE_LOGIN = 105U,

                /// Internal method
                INTERNAL_FUNCTION = 106U,

                /// Internal method
                INTERNAL_RENEW_GUID_TOKEN = 107U,

                /// Internal method
                INTERNAL_RENEW_TOKEN = 108U,

                /// Internal method (Deprecated)
                INTERNAL_CONVERT_ONLINE_TOKEN = 109U,

                /// Internal method
                INTERNAL_TRANSLATE_LANGUAGE = 110U,

                /// Internal method
                INTERNAL_GET_GAMEMETA = 111U,

                /// Internal method
                FORCE_REFRESH_TOKEN = 112U,

                /// Internal method
                ACCESS_TOKEN_RENEWED_TO_PRIVATE = 113U,

                /// Internal method
                GET_TOKEN_TO_PRIVATE = 114U,

                /// Internal method
                GET_ENV_TO_PRIVATE = 115U,

                /// Internal method
                GET_GAMEID_TO_PRIVATE = 116U,

                /// Internal method
                GET_MEMBERNO_TO_PRIVATE = 117U,

                /// Internal method
                GET_PUBLIC_IP = 118U,

                /// Internal method
                GET_TRANSLATE_LANGUAGE = 119U,

                /// Internal method
                GET_JSON_FROM_LAUNCHER_IPC_TO_PRIVATE = 120U,

                /// Internal method (VN 청소년 플레이타임 저장)
                INTERNAL_VN_SAVE_PLAYTIME = 121U,
            };

            /*!
            * @file     BaseSDKResult.h
            * \korean
            * @brief    BaseSDK에서 사용하는 함수의 Result Code
            * \endkorean
            * \english
            * @brief    Result Code of functions used in BaseSDK
            * \endenglish
            */
            enum class SDKResultCode : uint32_t
            {
                /*
                * Common Result
                */

                /*!
                * \korean
                * 0 : 성공
                * \endkorean
                * \english
                * 0 : Success
                * \endenglish
                */
                SUCCESS = 0U,

                /*!
                * \korean
                * 1 : 실패
                * \endkorean
                * \english
                * 1 : Fail
                * \endenglish
                */
                FAIL = 1U,

                /*!
                * \korean
                * 2 : Config 파일을 찾을 수 없습니다.
                * \endkorean
                * \english
                * 2 : Config file not found.
                * \endenglish
                */
                INVALID_CONFIG = 2U,

                /*!
                * \korean
                * 3 : 로그 레벨의 값이 유효하지 않습니다.
                * \endkorean
                * \english
                * 3 : The log level value is invalid.
                * \endenglish
                */
                INVALID_LOG_LEVEL = 3U,

                /*!
                * \korean
                * 4 : 로그 경로가 유효하지 않습니다.
                * \endkorean
                * \english
                * 4 : The log path is invalid.
                * \endenglish
                */
                INVALID_LOG_PATH = 4U,

                /*!
                * \korean
                * 5 : 잘못된 매개변수가 입력되었습니다.
                * \endkorean
                * \english
                * 5 : Invalid parameters entered.
                * \endenglish
                */
                INVALID_PARAM = 5U,

                /*!
                * \korean
                * 16 : BaseSDK가 Initialize가 되지 않았습니다.
                * \endkorean
                * \english
                * 16 : BaseSDK has not been initialized.
                * \endenglish
                */
                BASE_NOT_INITIALIZED = 16U,

                /*!
                * \korean
                * 17 : 초기화가 되지 않았습니다.
                * \endkorean
                * \english
                * 17 : Initialization has not been done.
                * \endenglish
                */
                NOT_INITIALIZED = 17U,

                /*!
                * \korean
                * 18 : 이미 초기화가 되었습니다.
                * \endkorean
                * \english
                * 18 : Already initialized.
                * \endenglish
                */
                ALREADY_INITIALIZED = 18U,

                /*!
                * \korean
                * 19 : AccessToken을 찾을 수 없습니다.
                * \endkorean
                * \english
                * 19 : AccessToken cannot be found.
                * \endenglish
                */
                INVALID_ACCESS_TOKEN = 19U,

                /*!
                * \korean
                * 20 : Token 객체를 찾을 수 없습니다.
                * \endkorean
                * \english
                * 20 : Token object not found.
                * \endenglish
                */
                NULL_TOKEN_ENTITY = 20U,

                /*!
                * \korean
                * 21 : 현재 객체를 찾을 수 없습니다.
                * \endkorean
                * \english
                * 21 : Unable to find the current object.
                * \endenglish
                */
                NULL_ENTITY = 21U,

                /*!
                * \korean
                * 22 : Http 통신 에러가 발생했습니다.
                * \endkorean
                * \english
                * 22 : Http communication error occurred.
                * \endenglish
                */
                HTTP_ERROR = 22U,

                /*!
                * \korean
                * 23 : Http API Response 에러가 발생했습니다.
                * \endkorean
                * \english
                * 23 : Http API Response error occurred.
                * \endenglish
                */
                RESPONSE_ERROR = 23U,

                /*!
                * \korean
                * 24 : Http API Response Code를 찾을 수 없습니다.
                * \endkorean
                * \english
                * 24 : Unable to find Http API Response Code.
                * \endenglish
                */
                RESPONSE_INVALID_CODE = 24U,

                /*!
                * \korean
                * 25 : Http API Response 값이 비어있습니다.
                * \endkorean
                * \english
                * 25 : Http API Response value is empty.
                * \endenglish
                */
                RESPONSE_VALUE_IS_NULL = 25U,

                /*!
                * \korean
                * 26 : Http API Response 포멧이 틀립니다.
                * \endkorean
                * \english
                * 26 : Http API Response format is incorrect.
                * \endenglish
                */
                RESPONSE_INVALID_VALUE_FORMAT = 26U,

                /*!
                * \korean
                * 27 : 81 Plug 전송을 실패했습니다. (Deprecated)
                * \endkorean
                * \english
                * 27 : 81 Plug transmission failed. (Deprecated)
                * \endenglish
                */
                LOG_81PLUG_ERROR = 27U,

                /*!
                * \korean
                * 28 : 81 Plug 업데이트를 실패했습니다. (Deprecated)
                * \endkorean
                * \english
                * 28 : 81 Plug update failed. (Deprecated)
                * \endenglish
                */
                UPDATE_81PLUG_FEED_ERROR = 28U,

                /*
                * \korean
                * 29 : 현재 비동기 작업이 진행중입니다.
                * \endkorean
                * \english
                * 29 : The current asynchronous operation is in progress.
                * \endenglish
                */
                ASYNC_OPERATION_IN_PROGRESS = 29U,

                /*!
                * \korean
                * 30 : BaseSDK를 Uninitialize하였습니다.
                * \endkorean
                * \english
                * 30 : BaseSDK has been Uninitialized.
                * \endenglish
                */
                BASE_UNINITIALIZED = 30U,

                /*!
                * \korean
                * 31 : 현재 국가에서는 지원되지 않는 기능입니다.
                * \endkorean
                * \english
                * 31 : This feature is not supported in the current country
                * \endenglish
                */
                NOT_SUPPORTED_COUNTRY = 31,

                /*!
                * \korean
                * 250 : Http API Response Json 예외가 발생하였습니다.
                * \endkorean
                * \english
                * 250 : Http API Response Json exception occurred.
                * \endenglish
                */
                JSON_EXCEPTION = 250,

                /*!
                * \korean
                * 251 : PC SDK DLL을 찾지 못했습니다.
                * \endkorean
                * \english
                * 251 : PC SDK DLL not found.
                * \endenglish
                */
                PCSDK_DLL_NOT_FOUND = 251U,

                /*!
                * \korean
                * 252 : 해당 내용은 구현되지 않았습니다.
                * \endkorean
                * \english
                * 252 : The content has not been implemented.
                * \endenglish
                */
                NOT_IMPLEMENTED = 252U,

                /*!
                * \korean
                * 253 : 관리되지 않는 예외가 발생하였습니다.
                * \endkorean
                * \english
                * 253 : An unmanaged exception occurred.
                * \endenglish
                */
                UNMANAGED_EXCEPTION = 253U,

                /*!
                * \korean
                * 254 : 관리되는 예외가 발생하였습니다.
                * \endkorean
                * \english
                * 254 : A managed exception occurred.
                * \endenglish
                */
                MANAGED_EXCEPTION = 254U,

                /*!
                * \korean
                * 255 : 알 수 없는 에러가 발생하였습니다.
                * \endkorean
                * \english
                * 255 : An unknown error occurred.
                * \endenglish
                */
                UNKNOWN_ERROR = 255U,

                /*
                * BaseSDK Result
                */

                /*!
                * \korean
                * 80 : 언어가 설정되지 않았습니다.
                * \endkorean
                * \english
                * 80 : Language not set.
                * \endenglish
                */
                LANGUAGE_NOT_SET = 80U,

                /*!
                * \korean
                * 81 : 번역할 문자열이 없습니다.
                * \endkorean
                * \english
                * 81 : There is no string to translate.
                * \endenglish
                */
                EMPTY_TRANSLATED_STRING = 81U,

                /*!
                * \korean
                * 82 : 필수 정보가 없습니다.
                * \endkorean
                * \english
                * 82 : Required information is missing.
                * \endenglish
                */
                NOT_FOUND_REQUIRED_INFORMATION = 82U,

                /*!
                * \korean
                * 83 : GDS 정보가 없습니다.
                * \endkorean
                * \english
                * 83 : GDS information is missing.
                * \endenglish
                */
                INVALID_GDS_INFO = 83U,

                /*!
                * \korean
                * 84 : 런처의 실행이 필요합니다.
                * \endkorean
                * \english
                * 84 : Launcher execution is required.
                * \endenglish
                */
                NEED_STOVE_LAUNCHER = 84U,

                /*!
                * \korean
                * 85 : 런처에서 필수값 생성을 실패하였습니다.
                * \endkorean
                * \english
                * 85 : Failed to create required values in the launcher.
                * \endenglish
                */
                LAUNCHER_FAILED_CREATE_REQUIRED = 85U,

                /*!
                * \korean
                * 86 : Token 갱신 시도 횟수를 초과했습니다.
                * \endkorean
                * \english
                * 86 : The number of attempts to renew the token has been exceeded.
                * \endenglish
                */
                RENEW_TOKEN_MAX_RETRY_COUNT_EXCEEDED = 86U,

                /*!
                * \korean
                * 87 : IPC 통신 연결을 실패하였습니다.
                * \endkorean
                * \english
                * 87 : IPC communication connection failed.
                * \endenglish
                */
                IPC_CONNECT_FAILED = 87U,

                /*!
                * \korean
                * 88 : IPC 통신에서 AES 암호키를 받지 못했습니다.
                * \endkorean
                * \english
                * 88 : AES encryption key not received in IPC communication.
                * \endenglish
                */
                IPC_AES_KEY_NOT_RECEIVED = 88U,

                /*!
                * \korean
                * 89 : IPC 통신에서 Timeout이 발생하였습니다.
                * \endkorean
                * \english
                * 89 : Timeout occurred in IPC communication.
                * \endenglish
                */
                IPC_TIMEOUT = 89U,
            };

            /*!
            * @file     BaseSDKResult.h
            * \korean
            * @brief    BaseSDK의 이름
            * \endkorean
            * \english
            * @brief    Name of BaseSDK
            * \endenglish
            */
            static const wchar_t* BaseSDKName = L"BaseSDK";
        }
    }
}