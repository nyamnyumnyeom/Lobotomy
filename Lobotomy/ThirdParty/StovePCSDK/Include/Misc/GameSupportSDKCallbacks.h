#pragma once

/*!
    * @file     Callbacks.h
    * \korean
    * @brief    GameSupportSDK에서 사용하는 Callback 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Callback values used in GameSupportSDK.
    * \endenglish
*/

#include "Misc/Result/Result.h"
#include "GameSupportSDKStructures.h"

// c style callbacks
namespace Stove
{
    namespace PCSDK
    {
        namespace GameSupport
        {
            /*!
            * \korean
            * @brief        GameSupport_Stat API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCStat stat 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the GameSupport_Stat API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCStat stat result value
            * \endenglish
            */
            typedef void(__cdecl* OnStatFinished)(CallbackResult callbackResult, StovePCStat stat);

            /*!
            * \korean
            * @brief        GameSupport_ModifyStat API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCModifyStatValue statValue 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the GameSupport_ModifyStat API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCModifyStatValue statValue result value
            * \endenglish
            */
            typedef void(__cdecl* OnModifyStatFinished)(CallbackResult callbackResult, StovePCModifyStatValue statValue);

            /*!
            * \korean
            * @brief        GameSupport_Achievement API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCAchievement achievement 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the GameSupport_Achievement API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCAchievement achievement result value
            * \endenglish
            */
            typedef void(__cdecl* OnAchievementFinished)(CallbackResult callbackResult, StovePCAchievement achievement);

            /*!
            * \korean
            * @brief        GameSupport_AllAchievement API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCAchievement* achievements StovePCAchievement 배열
            * @param[out]   uint32_t achievementSize StovePCAchievement 배열 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the GameSupport_AllAchievement API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCAchievement* achievements StovePCAchievement array
            * @param[out]   uint32_t achievementSize StovePCAchievement array size
            */
            typedef void(__cdecl* OnAllAchievementFinished)(CallbackResult callbackResult, StovePCAchievement* achievements, uint32_t achievementSize);

            /*!
            * \korean
            * @brief        GameSupport_Rank API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCRank* ranks StovePCRank 배열
            * @param[out]   uint32_t rankSize StovePCRank 배열 크기
            * @param[out]   uint32_t totalCount 총 데이터 갯수
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the GameSupport_Rank API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCRank* ranks StovePCRank array
            * @param[out]   uint32_t rankSize StovePCRank array size
            * @param[out]   uint32_t totalCount Total data count
            * \endenglish
            */
            typedef void(__cdecl* OnRankFinished)(CallbackResult callbackResult, StovePCRank* ranks, uint32_t rankSize, uint32_t totalCount);
        }
    }
}