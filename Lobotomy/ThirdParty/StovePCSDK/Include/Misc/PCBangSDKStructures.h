#pragma once

/*!
    * @file     Structures.h
    * \korean
    * @brief    PCBangSDK에서 사용하는 Structures 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Structures values used in PCBangSDK.
    * \endenglish
*/

#include <string>

#include "Misc/BaseSDKStructures.h"
#include "PCBangSDKEnumerations.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace PCBang
        {
            struct StovePCBangUserLoginCpp;
            struct StovePCBangStatusCpp;
            struct StovePCRefreshUserBenefitsCpp;

            /*!
            * @struct StovePCBangUserLogin
            * \korean
            * @brief PCBang_UserLogin API 호출시 응답받는 콜백의 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of the callback received when calling the PCBang_UserLogin API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCBangUserLogin
            {
            public:
                /*!
                * \korean
                * @brief    유저 혜택 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the user benefit code.
                * \endenglish
                * @return   PCBangPremium premiumStatus
                */
                PCBangPremium GetPremiumStatus() const;

                /*!
                * \korean
                * @brief    PC 방 고유번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the PC room serial number.
                * \endenglish
                * @return   int32_t pcBangSerialNumber
                */
                int32_t GetPCBangSerialNumber() const;

                /*!
                * \korean
                * @brief    PC 방 프리미엄 남은 시간을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the remaining time of the PC room premium.
                * \endenglish
                * @return   int32_t remainTime
                */
                int32_t GetRemainTime() const;

            public:
                StovePCBangUserLogin();
                StovePCBangUserLogin(const StovePCBangUserLogin& rhs);
                StovePCBangUserLogin(const StovePCBangUserLoginCpp* rhs);
                ~StovePCBangUserLogin();

                StovePCBangUserLogin& operator=(const StovePCBangUserLogin& rhs);
                StovePCBangUserLogin& operator=(const StovePCBangUserLoginCpp* rhs);

            private:
                void DeepCopy(const StovePCBangUserLogin& rhs);
                void DeepCopy(const StovePCBangUserLoginCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    유저 혜택 코드
                * @details  실패 시 전달되지 않음
                * \endkorean
                * \english
                * @brief    User benefit code
                * @details  not delivered in case of failure
                * \endenglish
                */
                PCBangPremium premiumStatus;

                /*!
                * \korean
                * @brief    PC 방 고유번호
                * @details  실패 시 전달되지 않음
                * \endkorean
                * \english
                * @brief    PC room serial number
                * @details  not delivered in case of failure
                * \endenglish
                */
                int32_t pcBangSerialNumber;

                /*!
                * \korean
                * @brief    PC 방 프리미엄 남은 시간
                * @details  실패 시 전달되지 않음
                * \endkorean
                * \english
                * @brief    Remaining time of PC room premium
                * @details  not delivered in case of failure
                * \endenglish
                */
                int32_t remainTime;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCBangStatus
            * \korean
            * @brief PCBang_CheckPCBangStatus API 호출시 응답받는 콜백의 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of the callback received when calling the PCBang_CheckPCBangStatus API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCBangStatus
            {
            public:
                /*!
                * \korean
                * @brief    유저 혜택 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the user benefit code.
                * \endenglish
                * @return   PCBangPremium premiumStatus
                */
                PCBangPremium GetPremiumStatus() const;

                /*!
                * \korean
                * @brief    PC 방 고유번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the PC room serial number.
                * \endenglish
                * @return   int32_t pcBangSerialNumber
                */
                int32_t GetPCBangSerialNumber() const;

                /*!
                * \korean
                * @brief    PC 방 상품코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the PC room product code.
                * \endenglish
                * @return   int32_t remainTime
                */
                int32_t GetProductCode() const;

            public:
                StovePCBangStatus();
                StovePCBangStatus(const StovePCBangStatus& rhs);
                StovePCBangStatus(const StovePCBangStatusCpp* rhs);
                ~StovePCBangStatus();

                StovePCBangStatus& operator=(const StovePCBangStatus& rhs);
                StovePCBangStatus& operator=(const StovePCBangStatusCpp* rhs);

            private:
                void DeepCopy(const StovePCBangStatus& rhs);
                void DeepCopy(const StovePCBangStatusCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    유저 혜택 코드
                * \endkorean
                * \english
                * @brief    User benefit code
                * \endenglish
                */
                PCBangPremium premiumStatus;

                /*!
                * \korean
                * @brief    PC 방 고유번호
                * \endkorean
                * \english
                * @brief    PC room serial number
                * \endenglish
                */
                int32_t pcBangSerialNumber;

                /*!
                * \korean
                * @brief    PC 방 상품코드
                * \endkorean
                * \english
                * @brief    PC room product code
                * \endenglish
                */
                int32_t productCode;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCRefreshUserBenefits
            * \korean
            * @brief PCBang_RefreshUserBenefits API 호출시 응답받는 콜백의 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of the callback received when calling the PCBang_RefreshUserBenefits API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCRefreshUserBenefits
            {
            public:
                /*!
                * \korean
                * @brief    유저 혜택 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the user benefit code.
                * \endenglish
                * @return   PCBangPremium premiumStatus
                */
                PCBangPremium GetPremiumStatus() const;

                /*!
                * \korean
                * @brief    PC 방 프리미엄 남은 시간을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the remaining time of the PC room premium.
                * \endenglish
                * @return   int32_t remainTime
                */
                int32_t GetRemainTime() const;

            public:
                StovePCRefreshUserBenefits();
                StovePCRefreshUserBenefits(const StovePCRefreshUserBenefitsCpp* rhs);
                ~StovePCRefreshUserBenefits();

                StovePCRefreshUserBenefits& operator=(const StovePCRefreshUserBenefitsCpp* rhs);

            private:
                void DeepCopy(const StovePCRefreshUserBenefitsCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    유저 혜택 코드
                * @details  실패 시 전달되지 않음
                * \endkorean
                * \english
                * @brief    User benefit code
                * @details  not delivered in case of failure
                * \endenglish
                */
                PCBangPremium premiumStatus;

                /*!
                * \korean
                * @brief    PC 방 프리미엄 남은 시간
                * @details  실패 시 전달되지 않음
                * \endkorean
                * \english
                * @brief    Remaining time of PC room premium
                * @details  not delivered in case of failure
                * \endenglish
                */
                int32_t remainTime;
            };
#pragma pack(pop)
        }
    }
}