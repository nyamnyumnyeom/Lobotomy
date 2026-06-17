#pragma once

/*!
    * @file     GameSupportSDK.h
    * \korean
    * @brief    GameSupportSDK에서 제공하는 함수의 헤더입니다.
    * \endkorean
    * \english
    * @brief    Header of functions provided by GameSupportSDK.
    * \endenglish
*/

#include <string>

#include "Misc/GameSupportSDKCallbacks.h"
#include "Misc/GameSupportSDKStructures.h"
#include "Misc/GameSupportSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace GameSupport
        {
            /*!
            * \korean
            * @brief GameSupportSDK를 초기화 합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Initialize GameSupportSDK.
            * @return class Result function call result
            * \endenglish
            */
            Result GameSupport_Initialize();

            /*!
            * \korean
            * @brief GameSupportSDK의 자원을 해제합니다.
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Release the resources of GameSupportSDK.
            * @return class Result function call result
            * \endenglish
            */
            Result GameSupport_UnInitialize();

            /*!
            * \korean
            * @brief 로그인한 사용자의 스탯을 등록한 Callback 함수에 넘겨줍니다.
            * @param[in] wchar_t* statId 조회할 Stat의 ID
            * @param[in] OnStatFinished onFinished 조회한 Stat의 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Pass the result of the user's stat to the registered Callback function.
            * @param[in] wchar_t* statId ID of the Stat to be queried
            * @param[in] OnStatFinished onFinished Callback function to receive the result of the queried Stat
            * \endenglish
            */
            void GameSupport_Stat(const wchar_t* statId, OnStatFinished onFinished);

            /*!
            * \korean
            * @brief 로그인한 사용자의 스탯을 설정합니다.
            * @param[in] wchar_t* statId 설정할 Stat의 ID
            * @param[in] int32_t statValue 설정할 Stat의 값
            * @param[in] OnModifyStatFinished onFinished 사용자의 스탯을 설정한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Set the user's stat.
            * @param[in] wchar_t* statId ID of the Stat to be set
            * @param[in] int32_t statValue Value of the Stat to be set
            * @param[in] OnModifyStatFinished onFinished Callback function to receive the result of setting the user's stat
            * \endenglish
            */
            void GameSupport_ModifyStat(const wchar_t* statId, int32_t statValue, OnModifyStatFinished onFinished);

            /*!
            * \korean
            * @brief 로그인한 사용자의 단일 업적을 조회합니다.
            * @param[in] wchar_t* achievementId 조회할 단일 업적 ID
            * @param[in] OnAchievementFinished onFinished 조회한 단일 업적의 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Query a single achievement of the logged-in user.
            * @param[in] wchar_t* achievementId ID of the single achievement to be queried
            * @param[in] OnAchievementFinished onFinished Callback function to receive the result of the queried single achievement
            * \endenglish
            */
            void GameSupport_Achievement(const wchar_t* achievementId, OnAchievementFinished onFinished);

            /*!
            * \korean
            * @brief 로그인한 사용자의 전체 업적을 조회합니다.
            * @param[in] OnAllAchievementFinished onFinished 조회한 전체 업적의 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Query all achievements of the logged-in user.
            * @param[in] OnAllAchievementFinished onFinished Callback function to receive the result of the queried all achievements
            * \endenglish
            */
            void GameSupport_AllAchievement(OnAllAchievementFinished onFinished);

            /*!
            * \korean
            * @brief 특정 페이지의 랭킹을 조회합니다.
            * @param[in] StovePCRankParams* rankParams 조회할 랭킹의 대한 정보
            * @param[in] OnRankFinished onFinished 조회한 랭킹의 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Query the ranking of a specific page.
            * @param[in] StovePCRankParams* rankParams Information about the ranking to be queried
            * @param[in] OnRankFinished onFinished Callback function to receive the result of the queried ranking
            * \endenglish
            */
            void GameSupport_Rank(const StovePCRankParams* rankParams, OnRankFinished onFinished);

            /*!
            * \korean
            * @brief GameSupportSDK의 버전 정보를 조회합니다.
            * @param[out] wchar_t* version 버전 정보
            * @param[in] uint32_t length 배열의 길이
            * @return class Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Query the version information of GameSupportSDK.
            * @param[out] wchar_t* version version information
            * @param[in] uint32_t length length of the array
            * @return class Result function call result
            * \endenglish
            */
            Result GameSupport_GetVersion(__out wchar_t* version, uint32_t length);
        }
    }
}