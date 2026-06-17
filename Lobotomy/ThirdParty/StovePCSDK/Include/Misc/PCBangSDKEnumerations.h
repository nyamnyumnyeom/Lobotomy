#pragma once

/*!
    * @file     Enumerations.h
    * \korean
    * @brief    PCBangSDK에서 사용하는 Enumerations 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Enumerations values used in PCBangSDK.
    * \endenglish
*/

#include <stdint.h>

namespace Stove
{
    namespace PCSDK
    {
        namespace PCBang
        {
            /*!
            * @enum class PCBangPremium
            * \korean
            * @brief PC방의 프리미엄을 확인하는 enum 값입니다.
            * \endkorean
            * \english
            * @brief Enum values to check the premium of the PC bang.
            * \endenglish
            */
            enum class PCBangPremium : int32_t
            {
                /*!
                * \korean
                * @brief 에러
                * \endkorean
                * \english
                * @brief Error
                * \endenglish
                */
                PCBANG_ERROR = -1,

                /*!
                * \korean
                * @brief 프리미엄
                * \endkorean
                * \english
                * @brief PREMIUM
                * \endenglish
                */
                PCBANG_PREMIUM = 1,

                /*!
                * \korean
                * @brief 무료가맹
                * \endkorean
                * \english
                * @brief FREE
                * \endenglish
                */
                PCBANG_FREE = 2,

                /*!
                * \korean
                * @brief 집(PC 방 이외) 무료가맹
                * \endkorean
                * \english
                * @brief FREE_OTHER
                * \endenglish
                */
                PCBANG_FREE_OTHER = 3,
            };
        }
    }
}