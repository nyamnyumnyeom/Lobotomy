#pragma once

/*!
    * @file     LogSDKResult.h
    * \korean
    * @brief    LogSDK에서 사용하는 Code값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Code values used in LogSDK.
    * \endenglish
*/

#include <stdint.h>

namespace Stove
{
    namespace PCSDK
    {
        namespace Log
        {
            /*!
            * @file     LogSDKResult.h
            * \korean
            * @brief    LogSDK에서 사용하는 함수들의 Code
            * \endkorean
            * \english
            * @brief    Code of functions used in LogSDK
            * \endenglish
            */
            enum class SDKMethod : uint32_t
            {
                /*
                * Common Method
                */

                /// 1 : Log_Initialize
                INITIALIZE = 1U,

                /// 2 : Log_UnInitialize
                UNINITIALIZE = 2U,

                /// 3 : Internal method (Deprecated)
                INTERNAL_SEND_81PLUG = 3U,

                /// 4 : Internal method (Deprecated)
                INTERNAL_UPDATE_81PLUG = 4U,

                /// 5 : Log_GetVersion
                GET_VERSION = 5U,

                /*
                * LogSDK Method
                */

                /// 80 : Log_Send
                LOG_SEND = 80U
            };

            /*!
            * @file     LogSDKResult.h
            * \korean
            * @brief    LogSDK에서 사용하는 함수의 Result Code
            * \endkorean
            * \english
            * @brief    Result Code of functions used in LogSDK
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
                * 5 : 유효한 매개변수가 입력되지 않았습니다.
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
                * 22 : Http 통신 오류가 발생했습니다.
                * \endkorean
                * \english
                * 22 : Http communication error occurred.
                * \endenglish
                */
                HTTP_ERROR = 22U,

                /*!
                * \korean
                * 23 : Http API Response 오류가 발생했습니다.
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
                * 26 : Http API Response 포맷이 올바르지 않습니다.
                * \endkorean
                * \english
                * 26 : Http API Response format is incorrect.
                * \endenglish
                */
                RESPONSE_INVALID_VALUE_FORMAT = 26U,

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
                * 30 : BaseSDK를 Uninitialize했습니다.
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
                * 251 : PC SDK DLL을 찾지 못했습니다.
                * \endkorean
                * \english
                * 251 : PC SDK DLL not found.
                * \endenglish
                */
                PCSDK_DLL_NOT_FOUND = 251U,

                /*!
                * \korean
                * 252 : 해당 내용이 구현되지 않았습니다.
                * \endkorean
                * \english
                * 252 : The content has not been implemented.
                * \endenglish
                */
                NOT_IMPLEMENTED = 252U,

                /*!
                * \korean
                * 253 : 관리되지 않는 예외가 발생했습니다.
                * \endkorean
                * \english
                * 253 : An unmanaged exception occurred.
                * \endenglish
                */
                UNMANAGED_EXCEPTION = 253U,

                /*!
                * \korean
                * 254 : 관리되는 예외가 발생했습니다.
                * \endkorean
                * \english
                * 254 : A managed exception occurred.
                * \endenglish
                */
                MANAGED_EXCEPTION = 254U,

                /*!
                * \korean
                * 255 : 알 수 없는 오류가 발생했습니다.
                * \endkorean
                * \english
                * 255 : An unknown error occurred.
                * \endenglish
                */
                UNKNOWN_ERROR = 255U,

                /*
                * LogSDK Result
                */

                /*!
                * \korean
                * 80 : 로컬 DB 작업 디렉토리 생성에 실패했습니다.
                * \endkorean
                * \english
                * 80 : Failed to create working directory for local DB.
                * \endenglish
                */
                LOCAL_DB_CREATE_WORKING_DIRECTORY_FAILED = 80U,

                /*!
                * \korean
                * 81 : 로컬 DB 연결에 실패했습니다.
                * \endkorean
                * \english
                * 81 : Failed to initialize local DB.
                * \endenglish
                */
                LOCAL_DB_CONNECT_FAILED = 81U,

                /*!
                * \korean
                * 82 : 로컬 DB 내 테이블 생성에 실패했습니다.
                * \endkorean
                * \english
                * 82 : Failed to create table in local DB.
                * \endenglish
                */
                LOCAL_DB_CREATE_TABLE_FAILED = 82U,

                /*!
                * \korean
                * 83 : 로컬 DB 연결 해제에 실패했습니다.
                * \endkorean
                * \english
                * 83 : Failed to initialize local DB.
                * \endenglish
                */
                LOCAL_DB_DISCONNECT_FAILED = 83U,

                /*!
                * \korean
                * 84 : 로컬 DB에 로그 백업에 실패했습니다.
                * \endkorean
                * \english
                * 84 : Failed to backup log to local DB.
                * \endenglish
                */
                LOCAL_DB_BACKUP_LOG_FAILED = 84U,

                /*!
                * \korean
                * 85 : 로그 전송 API를 호출할 매개변수가 올바르지 않습니다.
                * \endkorean
                * \english
                * 85 : The parameters to call the log transfer API are invalid.
                * \endenglish
                */
                INVALID_LOG_PARAMETER = 85U,

                /*!
                * \korean
                * 86 : 로그 크기가 최대 제한을 초과했습니다.
                * \endkorean
                * \english
                * 86 : Log size exceeds the maximum limit.
                * \endenglish
                */
                LOG_SIZE_EXCEEDED = 86U,
            };

            /*!
            * @file     LogSDKResult.h
            * \korean
            * @brief    LogSDK의 이름
            * \endkorean
            * \english
            * @brief    Name of LogSDK
            * \endenglish
            */
            static const wchar_t* LogSDKName = L"LogSDK";
        }
    }
}
