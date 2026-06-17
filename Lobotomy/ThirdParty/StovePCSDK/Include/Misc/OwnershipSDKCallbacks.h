#pragma once

/*!
    * @file     Callbacks.h
    * \korean
    * @brief    OwnershipSDK에서 사용하는 Callback 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Callback values used in OwnershipSDK.
    * \endenglish
*/

#include "OwnershipSDKStructures.h"

// Standard C style callbacks
namespace Stove
{
    namespace PCSDK
    {
        namespace Ownership
        {
            /*!
            * \korean
            * @brief        Ownership_OwnershipList API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCOwnership* ownerships StovePCOwnership 배열
            * @param[out]   uint32_t ownershipSize StovePCOwnership 배열의 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the Ownership_OwnershipList API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCOwnership* ownerships StovePCOwnership array
            * @param[out]   uint32_t ownershipSize Size of StovePCOwnership array
            * \endenglish
            */
            typedef void(__cdecl* OnOwnershipListFinished)(CallbackResult callbackResult, StovePCOwnership* ownerships, uint32_t ownershipSize);
        }
    }
}