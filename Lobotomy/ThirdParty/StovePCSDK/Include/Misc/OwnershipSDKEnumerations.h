#pragma once

/*!
    * @file     Enumerations.h
    * \korean
    * @brief    OwnershipSDK에서 사용하는 Enumerations 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Enumerations values used in OwnershipSDK.
    * \endenglish
*/

#include <stdint.h>

namespace Stove
{
    namespace PCSDK
    {
        namespace Ownership
        {
            /*!
            * @enum class OwnershipCode
            * \korean
            * @brief 소유권 획득 여부를 확인하기 위한 enum 값입니다.
            * \endkorean
            * \english
            * @brief Enum values to check ownership acquisition.
            * \endenglish
            */
            enum class OwnershipCode : uint32_t
            {
                /*!
                * \korean
                * @brief 소유권 없음
                * \endkorean
                * \english
                * @brief No ownership
                * \endenglish
                */
                NONE = 0,

                /*!
                * \korean
                * @brief 소유권 획득
                * \endkorean
                * \english
                * @brief Ownership acquisition
                * \endenglish
                */
                ACQUIRE = 1,

                /*!
                * \korean
                * @brief 소유권 해제
                * @details 구매 취소한 경우
                * \endkorean
                * \english
                * @brief Ownership release
                * @details in case of purchase cancellation
                * \endenglish
                */
                LOSE = 2,
            };

            /*!
            * @enum class OwnershipGameCode
            * \korean
            * @brief 게임의 타입을 확인하기 위한 enum 값입니다.
            * \endkorean
            * \english
            * @brief Enum values to check the type of the game.
            * \endenglish
            */
            enum class OwnershipGameCode : uint32_t
            {
                /*!
                * \korean
                * @brief 없음
                * \endkorean
                * \english
                * @brief None
                * \endenglish
                */
                NONE = 0,

                /*!
                * \korean
                * @brief 기본 게임
                * \endkorean
                * \english
                * @brief Basic game
                * \endenglish
                */
                BASIC = 3,

                /*!
                * \korean
                * @brief 데모 게임
                * \endkorean
                * \english
                * @brief DEMO game
                * \endenglish
                */
                DEMO = 4,

                /*!
                * \korean
                * @brief DLC 게임
                * \endkorean
                * \english
                * @brief DLC game
                * \endenglish
                */
                DLC = 5,
            };
        }
    }
}