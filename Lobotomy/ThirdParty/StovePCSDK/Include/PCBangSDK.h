#pragma once

/*!
    * @file     PCBangSDK.h
    * \korean
    * @brief    PCBangSDK에서 제공하는 함수의 헤더입니다.
    * \endkorean
    * \english
    * @brief    Header of functions provided by PCBangSDK.
    * \endenglish
*/

#include <string>
#include <Windows.h>

#include "Misc/PCBangSDKCallbacks.h"
#include "Misc/PCBangSDKStructures.h"
#include "Misc/PCBangSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace PCBang
        {
            /*!
            * \korean
            * @brief PCBangSDK를 초기화 합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Initialize PCBangSDK.
            * @return class Result function call result
            * \endenglish
            */
            Result PCBang_Initialize();
            
            /*!
            * \korean
            * @brief PCBangSDK의 자원을 해제합니다
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Release the resources of PCBangSDK
            * @return class Result function call result
            * \endenglish
            */
            Result PCBang_UnInitialize();
            
            /*!
            * \korean
            * @brief PC방 서비스에서 게임 유저 로그인합니다
            * @param[in] OnPCBangUserLoginOnFinished onUserLoginFinished 로그인의 결과를 넘겨받는 Callback 함수
            * @param[in] OnPCBangRefreshUserBenefitsOnFinished onRefreshBenefitsFinished 4분마다 갱신된 혜택의 정보를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Log in the game user from the PC Bang service
            * @param[in] OnPCBangUserLoginOnFinished onUserLoginFinished Callback function to receive the result of the login
            * @param[in] OnPCBangRefreshUserBenefitsOnFinished onRefreshBenefitsFinished Callback function to receive the updated benefit information every 4 minutes
            * \endenglish
            */
            void PCBang_UserLogin(OnPCBangUserLoginOnFinished onUserLoginFinished, OnPCBangRefreshUserBenefitsOnFinished onRefreshBenefitsFinished);

            /*!
            * \korean
            * @brief PC방 서비스에서 게임 유저 로그아웃합니다
            * @param[in] OnPCBangUserLogoutOnFinished onFinished 로그아웃의 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Log out the game user from the PC Bang service
            * @param[in] OnPCBangUserLogoutOnFinished onFinished Callback function to receive the result of the logout
            * \endenglish
            */
            void PCBang_UserLogout(OnPCBangUserLogoutOnFinished onFinished);
            
            /*!
            * \korean
            * @brief PC방 여부 및 상품 사용 상태 조회합니다
            * @param[in] OnPCBangCheckPCBangStatusOnFinished onFinished 로그아웃의 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Check the PC Bang status and product usage status
            * @param[in] OnPCBangCheckPCBangStatusOnFinished onFinished Callback function to receive the result of the logout
            * \endenglish
            */
            void PCBang_CheckPCBangStatus(OnPCBangCheckPCBangStatusOnFinished onFinished);
            
            /*!
            * \korean
            * @brief PCBangSDK의 버전 정보를 조회합니다.
            * @param[out] wchar_t* version 버전 정보
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Query the version information of PCBangSDK.
            * @param[out] wchar_t* version version information
            * @param[in] uint32_t length length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result PCBang_GetVersion(__out wchar_t* version, uint32_t length);
        }
    }
}