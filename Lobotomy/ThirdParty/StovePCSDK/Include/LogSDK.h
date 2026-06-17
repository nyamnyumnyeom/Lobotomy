#pragma once

/*!
    * @file     LogSDK.h
    * \korean
    * @brief    LogSDK에서 제공하는 함수들의 헤더입니다.
    * \endkorean
    * \english
    * @brief    Header of functions provided by LogSDK.
    * \endenglish
*/

#include <string>
#include <Windows.h>

#include "Misc/LogSDKCallbacks.h"
#include "Misc/LogSDKStructures.h"
#include "Misc/LogSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Log
        {
            /*!
            * \korean
            * @brief LogSDK를 초기화합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Initialize LogSDK.
            * @return class Result function call result
            * \endenglish
            */
            Result Log_Initialize();

            /*!
            * \korean
            * @brief LogSDK의 리소스를 해제합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Release the resources of LogSDK
            * @return class Result function call result
            * \endenglish
            */
            Result Log_UnInitialize();

            /*!
            * \korean
            * @brief STOVE 로그 서버에 로그를 전송합니다.
            * @param[in] StovePCLogSendParam* logSendParam 로그를 전송하기 위한 정보
            * @param[in] OnLogSendFinished onFinished 로그 전송 결과를 전달받는 Callback 함수
            * \endkorean
            * \english
            * @brief Send log to STOVE log server.
            * @param[in] StovePCLogSendParam* logSendParam Information for sending log
            * @param[in] OnLogSendFinished onFinished Callback function to receive the result of log transmission
            * \endenglish
            */
            void Log_Send(const StovePCLogSendParam* logSendParam, OnLogSendFinished onFinished);

            /*!
            * \korean
            * @brief LogSDK의 버전 정보를 조회합니다.
            * @param[out] wchar_t* version 버전 정보
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Query the version information of LogSDK.
            * @param[out] wchar_t* version Version information
            * @param[in] uint32_t length Length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result Log_GetVersion(__out wchar_t* version, uint32_t length);
        }
    }
}