#pragma once

/*!
    * @file     Callbacks.h
    * \korean
    * @brief    PCBangSDK에서 사용하는 Callback 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Callback values used in PCBangSDK.
    * \endenglish
*/

#include "PCBangSDKStructures.h"

// Standard C style callbacks
namespace Stove
{
    namespace PCSDK
    {
        namespace PCBang
        {
            /*!
            * \korean
            * @brief        PCBang_UserLogin API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCBangUserLogin userLogin 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the PCBang_UserLogin API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCBangUserLogin userLogin result value
            * \endenglish
            */
            typedef void(__cdecl* OnPCBangUserLoginOnFinished)(CallbackResult callbackResult, StovePCBangUserLogin userLogin);

            /*!
            * \korean
            * @brief        PCBang_UserLogin API 호출 시 응답받는 콜백 함수 포인터
            * @details      4분마다 유저의 갱신된 혜택 정보를 넘겨받는 Callback 함수
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCRefreshUserBenefits refreshUserBenefits 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the PCBang_UserLogin API
            * @details      Callback function that receives the user's updated benefits information every 4 minutes
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCRefreshUserBenefits refreshUserBenefits result value
            * \endenglish
            */
            typedef void(__cdecl* OnPCBangRefreshUserBenefitsOnFinished)(CallbackResult callbackResult, StovePCRefreshUserBenefits refreshUserBenefits);

            /*!
            * \korean
            * @brief        PCBang_UserLogout API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the PCBang_UserLogout API
            * @param[out]   CallbackResult callbackResult Callback result value
            * \endenglish
            */
            typedef void(__cdecl* OnPCBangUserLogoutOnFinished)(CallbackResult callbackResult);

            /*!
            * \korean
            * @brief        PCBang_CheckPCBangStatus API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCBangStatus pcBangStatus 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the PCBang_CheckPCBangStatus API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCBangStatus pcBangStatus result value
            * \endenglish
            */
            typedef void(__cdecl* OnPCBangCheckPCBangStatusOnFinished)(CallbackResult callbackResult, StovePCBangStatus pcBangStatus);
        }
    }
}