#pragma once

/*!
    * @file     Enumerations.h
    * \korean
    * @brief    IAPSDK에서 사용하는 Enumerations 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Enumerations values used in IAPSDK.
    * \endenglish
*/

#include <stdint.h>

namespace Stove
{
    namespace PCSDK
    {
        namespace IAP
        {
            /*!
            * @enum StovePCPurchaseOperation
            * \korean
            * @brief IAP_StartPurchase 메소드 수행 시 동작을 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the operation when IAP_StartPurchase method is executed.
            * \endenglish
            */
            enum class StovePCPurchaseOperation : uint32_t
            {
                /*!
                * \korean
                * 가장 기초적인 동작입니다. Stove Webview를 사용하지 않고 인게임 결제를 수동으로 연동하는 경우에 사용합니다.
                * 결과에 포함된 일회용 URL을 통해 Stove 웹 결제 페이지를 별도로 열어서 결제를 진행해야 합니다.
                * 결제 진행 후 IAP_ConfirmPurchase API를 수동으로 호출하여 구매 결과를 확인할 수 있습니다.
                * \endkorean
                * \english
                * The most basic operation. Used when integrating in-game purchases manually without using Stove Webview.
                * You must open the Stove web payment page separately using the one-time URL included in the result.
                * After the payment is completed, you can manually call the IAP_ConfirmPurchase API to check the purchase result.
                * \endenglish
                */
                DEFAULT = 0,

                /*!
                * \korean
                * Stove Webview를 통해 Stove 웹 결제 페이지를 열고 인게임 결제를 진행합니다.
                * 웹뷰 내에서 결제 진행 후 IAP_ConfirmPurchase API를 수동으로 호출하여 구매 결과를 확인할 수 있습니다.
                * \endkorean
                * \english
                * Open the Stove web payment page through Stove Webview and proceed with in-game payment.
                * You can manually call the IAP_ConfirmPurchase API to check the purchase result after the payment is completed in the webview.
                * \endenglish
                */
                WITH_WEBVIEW = 1,

                /*!
                * \korean
                * (권장) Stove Webview를 통해 Stove 웹 결제 페이지를 열고 인게임 결제를 진행하고,
                * 결제가 성공적으로 완료되면 IAP_ConfirmPurchase API를 자동으로 호출하여 구매 결과를 확인하여 반환합니다.
                * \endkorean
                * \english
                * (Recommended) Open the Stove web payment page through Stove Webview and proceed with in-game payment.
                * If the payment is successfully completed, the IAP_ConfirmPurchase API is automatically called to check and return the purchase result.
                * \endenglish
                */
                WITH_WEBVIEW_AND_CONFIRM_RESULT = 2,

                /*!
                * \korean
                * StovePCPurchaseOperation의 끝을 나타내는 값이며 유효한 operation이 아닙니다.
                * \endkorean
                * \english
                * The end of StovePCPurchaseOperation, and it is not a valid operation.
                * \endenglish
                */
                _MAX_COUNT
            };

            /*!
            * @enum StovePCPaymentOperation
            * \korean
            * @brief IAP_StartPayment 메소드 수행 시 동작을 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the operation when IAP_StartPayment method is executed.
            * \endenglish
            */
            enum class StovePCPaymentOperation : uint32_t
            {
                /*!
                * \korean
                * 가장 기초적인 동작입니다. Stove Webview를 사용하지 않고 게임 캐시 구매를 수동으로 연동하는 경우에 사용합니다.
                * 결과에 포함된 일회용 URL을 통해 Stove 웹 결제 페이지를 별도로 열어서 결제를 진행해야 합니다.
                * \endkorean
                * \english
                * The most basic operation. Used when integrating game cash purchases manually without using Stove Webview.
                * You must open the Stove web payment page separately using the one-time URL included in the result.
                * \endenglish
                */
                DEFAULT = 0,

                /*!
                * \korean
                * Stove Webview를 통해 Stove 웹 결제 페이지를 열고 게임 캐시 구매를 진행합니다.
                * \endkorean
                * \english
                * Open the Stove web payment page through Stove Webview and proceed with the game cash purchase.
                * \endenglish
                */
                WITH_WEBVIEW = 1,

                /*!
                * \korean
                * StovePCPaymentOperation의 끝을 나타내는 값이며 유효한 operation이 아닙니다.
                * \endkorean
                * \english
                * The end of StovePCPaymentOperation, and it is not a valid operation.
                * \endenglish
                */
                _MAX_COUNT
            };

            /*!
            * @enum StovePCTermsOperation
            * \korean
            * @brief IAP_FetchTermsAgreement 메소드 수행 시 동작을 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the operation when IAP_FetchTermsAgreement method is executed.
            * \endenglish
            */
            enum class StovePCTermsOperation : uint32_t
            {
                /*!
                * \korean
                * 가장 기초적인 동작입니다. Stove Webview를 사용하지 않고 약관 동의를 수동으로 연동하는 경우에 사용합니다.
                * 결과에 포함된 일회용 URL을 통해 웹 페이지를 별도로 열어서 약관 동의를 진행해야 합니다.
                * \endkorean
                * \english
                * The most basic operation. Used when integrating terms of service agreement manually without using Stove Webview.
                * You must open a web page separately using the one-time URL included in the result to proceed with the terms of service agreement.
                * \endenglish
                */
                DEFAULT = 0,

                /*!
                * \korean
                * Stove Webview를 통해 웹 페이지를 열고 약관 동의를 진행합니다.
                * \endkorean
                * \english
                * Open the web page through Stove Webview and proceed with the terms of service agreement.
                * \endenglish
                */
                WITH_WEBVIEW = 1,

                /*!
                * \korean
                * StovePCTermsOperation의 끝을 나타내는 값이며 유효한 operation이 아닙니다.
                * \endkorean
                * \english
                * The end of StovePCTermsOperation, and it is not a valid operation.
                * \endenglish
                */
                _MAX_COUNT
            };

            /*!
            * @enum ProductTypeCode
            * \korean
            * @brief 아이템 유형 코드를 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the item type code.
            * \endenglish
            */
            enum class ProductTypeCode : uint32_t
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
                * @brief 인디 패키지 게임 아이템
                * \endkorean
                * \english
                * @brief Indie package game item
                * \endenglish
                */
                INDIE_PACKAGE_GAME_ITEM = 1,

                /*!
                * \korean
                * @brief 인 게임 아이템
                * \endkorean
                * \english
                * @brief In-game item
                * \endenglish
                */
                IN_GAME_ITEM = 2,

                /*!
                * \korean
                * @brief 패키지 아이템
                * \endkorean
                * \english
                * @brief Package item
                * \endenglish
                */
                PACKAGE_ITEM = 3,
            };

            /*!
            * @enum DiscountType
            * \korean
            * @brief 할인 유형 코드를 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the discount type code.
            * \endenglish
            */
            enum class DiscountType : uint32_t
            {
                /*!
                * \korean
                * @brief 할인 없음
                * \endkorean
                * \english
                * @brief No discount
                * \endenglish
                */
                NONE = 0,

                /*!
                * \korean
                * @brief 정률 할인
                * \endkorean
                * \english
                * @brief Fixed rate discount
                * \endenglish
                */
                FIXED_RATE = 1,

                /*!
                * \korean
                * @brief 정액 할인
                * \endkorean
                * \english
                * @brief Fixed amount discount
                * \endenglish
                */
                FLAT_RATE = 2,
            };

            /*!
            * @enum PurchaseLimitTypeCode
            * \korean
            * @brief 구매 제한 유형 코드를 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the purchase limit type code.
            * \endenglish
            */
            enum class PurchaseLimitTypeCode : uint32_t
            {
                /*!
                * \korean
                * @brief 제한 없음
                * \endkorean
                * \english
                * @brief No limit
                * \endenglish
                */
                NONE = 0,

                /*!
                * \korean
                * @brief 무제한
                * \endkorean
                * \english
                * @brief Unlimited
                * \endenglish
                */
                UNLIMITED = 1,

                /*!
                * \korean
                * @brief 회원별 제한
                * \endkorean
                * \english
                * @brief Member limit
                * \endenglish
                */
                MEMBER = 2,

                /*!
                * \korean
                * @brief 캐릭터별 제한
                * \endkorean
                * \english
                * @brief Character limit
                * \endenglish
                */
                CHARACTER = 3
            };

            /*!
            * @enum PurchaseProgress
            * \korean
            * @brief 구매 진행 상태를 나타내는 enum 타입입니다.
            * \endkorean
            * \english
            * @brief Enum type that represents the purchase progress status.
            * \endenglish
            */
            enum class PurchaseProgress : uint32_t
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
                * @brief 일회용 결제 URL로 결제 창 호출 필요
                * \endkorean
                * \english
                * @brief Need to call the payment window with a one-time payment URL
                * \endenglish
                */
                NEED_PAYMENT_WINDOW = 1,

                /*!
                * \korean
                * @brief 0원 구매로 결제가 완료되었거나 Webview 사용으로 인해 URL 수동 호출 불필요
                * \endkorean
                * \english
                * @brief Payment is completed with a 0 won purchase or manual URL call is not required due to Webview usage
                * \endenglish
                */
                NOT_NEED_PAYMENT_WINDOW = 2
            };

            /*!
            * @enum StovePCVoidedPurchasesMarketType
            * \korean
            * @brief 비정상 환불 내역을 조회할 마켓을 나타내는 enum 타입입니다. (for IAP_FetchVoidedPurchasesEx)
            * \endkorean
            * \english
            * @brief Enum type that represents the market to query abnormal refund history. (for IAP_FetchVoidedPurchasesEx)
            * \endenglish
            */
            enum class StovePCVoidedPurchasesMarketType : uint32_t
            {
                /*!
                * \korean
                * @brief  모든 마켓 조회
                * \endkorean
                * \english
                * @brief  Query all markets
                * \endenglish
                */
                ALL = 0,

                /*!
                * \korean
                * @brief 스팀 마켓 조회
                * \endkorean
                * \english
                * @brief Query Steam market
                * \endenglish
                */
                STEAM = 1,

                /*!
                * \korean
                * @brief 구글 플레이 마켓 조회
                * \endkorean
                * \english
                * @brief Query Google Play market
                * \endenglish
                */
                GOOGLE_PLAY = 2,

                /*!
                * \korean
                * @brief 애플 앱 스토어 조회
                * \endkorean
                * \english
                * @brief Query Apple App Store
                * \endenglish
                */
                APPLE_APP_STORE = 3
            };
        }
    }
}