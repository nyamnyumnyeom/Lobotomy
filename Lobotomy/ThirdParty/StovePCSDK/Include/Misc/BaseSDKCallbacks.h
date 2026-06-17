#pragma once

/*!
    * @file     Callbacks.h
    * \korean
    * @brief    BaseSDK에서 사용하는 Callback 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Callback values used in BaseSDK.
    * \endenglish
*/

#include "BaseSDKStructures.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Base
        {
            /*!
            * \korean
            * @brief        Base_RestartAppIfNecessaryAsync API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   bool restartAppIfNecessary 앱의 재실행이 필요한지 여부
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_RestartAppIfNecessaryAsync API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   bool restartAppIfNecessary Whether the app needs to be restarted
            * \endenglish
            */
            typedef void(__cdecl* OnRestartAppIfNecessaryAsyncFinished)(CallbackResult callbackResult, bool restartAppIfNecessary);

            /*!
            * \korean
            * @brief        Base_Initialize API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_Initialize API
            * @param[out]   CallbackResult callbackResult Callback result value
            * \endenglish
            */
            typedef void(__cdecl* OnInitializeFinished)(CallbackResult callbackResult);

            /*!
            * \korean
            * @brief        Base_OverImmersionNotification API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCOverImmersion overImmersion 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_OverImmersionNotification API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCOverImmersion overImmersion result value
            * \endenglish
            */
            typedef void(__cdecl* OnOverImmersionFinished)(CallbackResult callbackResult, StovePCOverImmersion overImmersion);

            /*!
            * \korean
            * @brief        Base_ShutdownNotification API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCShutdown shutdown 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_ShutdownNotification API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCShutdown shutdown result value
            * \endenglish
            */
            typedef void(__cdecl* OnShutdownFinished)(CallbackResult callbackResult, StovePCShutdown shutdown);


            /*!
            *\korean
            * @brief        외부 브라우저를 통해 URL을 열었을 때 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when opening a URL through an external browser
            * @param[out]   CallbackResult callbackResult Callback result value
            * \endenglish
            */
            typedef void(__cdecl* OnOpenExternalUrlFinished)(CallbackResult callbackResult);


            /*!
            * \korean
            * @brief        Base_AccessTokenRenewed API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCToken token 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_AccessTokenRenewed API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCToken token result value
            * \endenglish
            */
            typedef void(__cdecl* OnRenewTokenFinished)(CallbackResult callbackResult, StovePCToken token);

            /*!
            * \korean
            * @brief        Base_VietnamAgeRatingNotification API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCVietnamAgeRatingInfo vietnamAgeRatingInfo 베트남 연령 등급 정보
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_VietnamAgeRatingNotification API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCVietnamAgeRatingInfo vietnamAgeRatingInfo Vietnam age rating info
            * \endenglish
            */
            typedef void(__cdecl* OnVietnamAgeRatingFinished)(CallbackResult callbackResult, StovePCVietnamAgeRatingInfo vietnamAgeRatingInfo);

            /*!
            * \korean
            * @brief        Base_VietnamOverimmersionNotification API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCVietnamOverimmersionInfo vietnamOverimmersionInfo 베트남 과몰입 정보
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Base_VietnamOverimmersionNotification API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCVietnamOverimmersionInfo vietnamOverimmersionInfo Vietnam overimmersion info
            * \endenglish
            */
            typedef void(__cdecl* OnVietnamOverimmersionFinished)(CallbackResult callbackResult, StovePCVietnamOverimmersionInfo vietnamOverimmersionInfo);
        }
    }
}
