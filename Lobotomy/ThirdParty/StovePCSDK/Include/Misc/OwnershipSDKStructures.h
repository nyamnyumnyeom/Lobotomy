#pragma once

/*!
    * @file     Structures.h
    * \korean
    * @brief    OwnershipSDK에서 사용하는 Structures 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Structures values used in OwnershipSDK.
    * \endenglish
*/

#include <string>

#include "Misc/BaseSDKStructures.h"

#include "OwnershipSDKEnumerations.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Ownership
        {
            struct StovePCOwnershipCpp;

            /*!
            * @struct StovePCOwnership
            * \korean
            * @brief Ownership_OwnershipList 관련 API 호출시 응답받는 콜백의 OwnerShip 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of Ownership received when calling the Ownership_OwnershipList related API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCOwnership
            {
            public:
                /*!
                * \korean
                * @brief    게임 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game ID.
                * \endenglish
                * @return   const wchar_t* gameId
                */
                const wchar_t* GetGameId() const;

                /*!
                * \korean
                * @brief    게임 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game code.
                * \endenglish
                * @return   OwnershipGameCode gameCode
                */
                OwnershipGameCode GetGameCode() const;

                /*!
                * \korean
                * @brief    Ownership 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Ownership code.
                * \endenglish
                * @return   OwnershipCode ownershipCode
                */
                OwnershipCode GetOwnershipCode() const;

                /*!
                * \korean
                * @brief    Ownership 구매날짜를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Ownership purchase date.
                * \endenglish
                * @return   uint64_t purchaseDate
                */
                uint64_t GetPurchaseDate() const;

            public:
                StovePCOwnership();
                StovePCOwnership(const StovePCOwnership& rhs);
                StovePCOwnership(const StovePCOwnershipCpp* rhs);
                ~StovePCOwnership();

                StovePCOwnership& operator=(const StovePCOwnership& rhs);
                StovePCOwnership& operator=(const StovePCOwnershipCpp* rhs);

            private:
                void DeepCopy(const StovePCOwnership& rhs);
                void DeepCopy(const StovePCOwnershipCpp* rhs);


            private:
                /*!
                * \korean
                * @brief    Ownership 게임 아이디
                * \endkorean
                * \english
                * @brief    Ownership Game ID
                * \endenglish
                */
                wchar_t* gameId = nullptr;

                /*!
                * \korean
                * @brief    Ownership 게임 코드
                * \endkorean
                * \english
                * @brief    Ownership Game Code
                * \endenglish
                */
                OwnershipGameCode gameCode;

                /*!
                * \korean
                * @brief    Ownership 코드
                * \endkorean
                * \english
                * @brief    Ownership code
                * \endenglish
                */
                OwnershipCode ownershipCode;

                /*!
                * \korean
                * @brief    Ownership 구매날짜
                * \endkorean
                * \english
                * @brief    Ownership purchase date
                * \endenglish
                */
                uint64_t purchaseDate;
            };
#pragma pack(pop)
        }
    }
}