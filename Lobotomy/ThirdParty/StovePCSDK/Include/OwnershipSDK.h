#pragma once

/*!
    * @file     OwnershipSDK.h
    * \korean
    * @brief    OwnershipSDK에서 제공하는 함수의 헤더입니다.
    * \endkorean
    * \english
    * @brief    Header of functions provided by OwnershipSDK.
    * \endenglish
*/

#include <string>
#include <Windows.h>

#include "Misc/OwnershipSDKCallbacks.h"
#include "Misc/OwnershipSDKStructures.h"
#include "Misc/OwnershipSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Ownership
        {
            /*!
            * \korean
            * @brief OwnershipSDK를 초기화 합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Initialize OwnershipSDK.
            * @return class Result function call result
            * \endenglish
            */
            Result Ownership_Initialize();

            /*!
            * \korean
            * @brief OwnershipSDK의 자원을 해제합니다
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Release the resources of OwnershipSDK
            * @return class Result function call result
            * \endenglish
            */
            Result Ownership_UnInitialize();

            /*!
            * \korean
            * @brief 현재 실행된 게임의 소유권을 조회합니다
            * @param[in] OnOwnershipListFinished onFinished 현재 실행된 게임의 소유권에 대한 정보를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Query the ownership of the currently running game
            * @param[in] OnOwnershipListFinished onFinished Callback function to receive information about the ownership of the currently running game
            * \endenglish
            */
            void Ownership_OwnershipList(OnOwnershipListFinished onFinished);

            /*!
            * \korean
            * @brief OwnershipSDK의 버전 정보를 조회합니다.
            * @param[out] wchar_t* version 버전 정보
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Query the version information of OwnershipSDK.
            * @param[out] wchar_t* version Version information
            * @param[in] uint32_t length Length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result Ownership_GetVersion(__out wchar_t* version, uint32_t length);
        }
    }
}