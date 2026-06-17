#pragma once

/*!
    * @file     Callbacks.h
    * \korean
    * @brief    LogSDK에서 사용하는 Callback 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Callback values used in LogSDK.
    * \endenglish
*/

#include "LogSDKStructures.h"

// Standard C style callbacks
namespace Stove
{
    namespace PCSDK
    {
        namespace Log
        {
            /*!
            * \korean
            * @brief        Log_LogSend API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Log_LogSend API
            * @param[out]   CallbackResult callbackResult Callback result value
            * \endenglish
            */
            typedef void(__cdecl* OnLogSendFinished)(CallbackResult callbackResult);
        }
    }
}
