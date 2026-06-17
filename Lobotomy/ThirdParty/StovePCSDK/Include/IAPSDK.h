#pragma once

/*!
    * @file     IAPSDK.h
    * \korean
    * @brief    IAPSDK에서 제공하는 함수의 헤더입니다.
    * \endkorean
    * \english
    * @brief    Header of functions provided by IAPSDK.
    * \endenglish
*/

#include <string>
#include <Windows.h>

#include "Misc/IAPSDKCallbacks.h"
#include "Misc/IAPSDKStructures.h"
#include "Misc/IAPSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace IAP
        {
            /*!
            * \korean
            * @brief IAPSDK를 초기화 합니다.
            * @param[in] wchar_t* shopKey 파트너스로부터 발급받은 shopKey
            * @return struct Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Initialize IAPSDK.
            * @param[in] wchar_t* shopKey shopKey issued by the partner
            * @return struct Result function call result
            * \endenglish
            */
            Result IAP_Initialize(const wchar_t* shopKey);

            /*!
            * \korean
            * @brief IAPSDK를 초기화 합니다. Internal Style 팝업의 부모 윈도우가 될 메인 윈도우 핸들이 필요합니다.
            * @param[in] wchar_t* shopKey 파트너스로부터 발급받은 shopKey
            * @param[in] void* mainWndHandle Internal Style 팝업의 부모 윈도우가 될 메인 윈도우 핸들 (HWND)
            * @return struct Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Initialize IAPSDK. The main window handle that will be the parent window of the Internal Style payment window is required.
            * @param[in] wchar_t* shopKey shopKey issued by the partner
            * @param[in] void* mainWndHandle Main window handle (HWND) that will be the parent window of the Internal Style popup
            * @return struct Result function call result
            * \endenglish
            */
            Result IAP_InitializeWithWndInfo(const wchar_t* shopKey, const void* mainWndHandle);

            /*!
            * \korean
            * @brief IAPSDK의 자원을 해제합니다
            * @return struct Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Release the resources of IAPSDK
            * @return struct Result function call result
            * \endenglish
            */
            Result IAP_UnInitialize();

            /*!
            * \korean
            * @brief 스토브 플랫폼에 등록된 상점 카테코리를 조회합니다.
            * @param[in] OnFetchShopCategoriesFinished onFinished 상점 카테고리에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Fetch shop categories registered on the Stove platform.
            * @param[in] OnFetchShopCategoriesFinished onFinished Callback function that registers information about shop categories
            * \endenglish
            */
            void IAP_FetchShopCategories(OnFetchShopCategoriesFinished onFinished);

            /*!
            * \korean
            * @brief 스토브 플랫폼에 등록된 상품 정보를 조회합니다.
            * @param[in] StovePCFetchProductParam* params 조회할 상품 정보
            * @param[in] OnFetchProductsFinished onFinished 조회한 상점에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Fetch product information registered on the Stove platform.
            * @param[in] StovePCFetchProductParam* params Product information to be retrieved
            * @param[in] OnFetchProductsFinished onFinished Callback function that registers information about the store
            * \endenglish
            */
            void IAP_FetchProducts(const StovePCFetchProductParam* params, OnFetchProductsFinished onFinished);

            /*!
            * \korean
            * @brief 스토브 플랫폼에 등록된 상품 정보를 조회합니다. (응답에  구매 가능 코드 (purchase_availability_code) 추가)
            * @param[in] StovePCFetchProductParam* params 조회할 상품 정보
            * @param[in] OnFetchProductsExFinished onFinished 조회한 상점에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Fetch product information registered on the Stove platform.
            * @param[in] StovePCFetchProductParam* params Product information to be retrieved
            * @param[in] OnFetchProductsExFinished onFinished Callback function that registers information about the store
            * \endenglish
            */
            void IAP_FetchProductsEx(const StovePCFetchProductParam* params, OnFetchProductsExFinished onFinished);

            /*!
            * \korean
            * @brief 상품구매를 시작하기 위한 결제 URL 을 전달받거나 WebView2를 이용하여 결제를 시작합니다.
            * @param[in] StovePCStartPurchaseParam* params 상품 구매에 대한 정보
            * @param[in] OnStartPurchaseFinished onFinished 상품 구매에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Receive the payment URL to start purchasing the product or start the payment using WebView2.
            * @param[in] StovePCStartPurchaseParam* params Information about the product purchase
            * @param[in] OnStartPurchaseFinished onFinished Callback function that registers information about the product purchase
            * \endenglish
            */
            void IAP_StartPurchase(const StovePCStartPurchaseParam* params, OnStartPurchaseFinished onFinished);

            /*!
            * \korean
            * @brief 상품구매를 시작하기 위한 결제 URL 을 전달받거나 WebView2를 이용하여 결제를 시작합니다.
            * @param[in] StovePCStartPurchaseParam* params 상품 구매에 대한 정보
            * @param[in] OnStartPurchaseFinished onFinished 상품 구매에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * @param[in] OnIAPPopupDestroyFinished onDestroy 팝업이 닫힐 경우에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Receive the payment URL to start purchasing the product or start the payment using WebView2.
            * @param[in] StovePCStartPurchaseParam* params Information about the product purchase
            * @param[in] OnStartPurchaseFinished onFinished Callback function that registers information about the product purchase
            * @param[in] OnIAPPopupDestroyFinished onDestroy Callback function to receive the result when the popup is closed
            * \endenglish
            */
            void IAP_StartPurchaseEx(const StovePCStartPurchaseParam* params,
                                     OnStartPurchaseFinished onFinished, OnIAPPopupDestroyFinished onDestroy);
            /*!
            * \korean
            * @brief 상품구매 완료후 구매 ID로 정상처리 되었는지 확인 합니다.
            * @param[in] int64_t transactionMasterNumber 주문 마스터 번호
            * @param[in] OnConfirmPurchaseFinished onFinished 상품 구매 완료에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Check if the purchase ID has been processed correctly after the product purchase is completed.
            * @param[in] int64_t transactionMasterNumber Order master number
            * @param[in] OnConfirmPurchaseFinished onFinished Callback function that registers information about the product purchase completion
            * \endenglish
            */
            void IAP_ConfirmPurchase(int64_t transactionMasterNumber, OnConfirmPurchaseFinished onFinished);

            /*!
            * \korean
            * @brief 전체 구매한 상품목록을 조회합니다.
            * @param[in] OnFetchInventoryFinished onFinished 전체 구매한 상품목록에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Retrieve a list of all purchased products.
            * @param[in] OnFetchInventoryFinished onFinished Callback function that registers information about all purchased products
            * \endenglish
            */
            void IAP_FetchInventory(OnFetchInventoryFinished onFinished);

            /*!
            * \korean
            * @brief 필수 약관 동의 여부를 조회합니다.
            * @param[in] StovePCTermsOption* options API에 대한 옵션을 전달하는 구조체입니다
            * @param[in] OnFetchTermsAgreementFinished onFinished 필수 약관 동의에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Check whether the user has agreed to the required terms.
            * @param[in] StovePCTermsOption* options Structure that passes options for the API
            * @param[in] OnFetchTermsAgreementFinished onFinished Callback function that registers information about the required terms agreement
            * \endenglish
            */
            void IAP_FetchTermsAgreement(const StovePCTermsOption* options, OnFetchTermsAgreementFinished onFinished);

            /*!
            * \korean
            * @brief 필수 약관 동의 여부를 조회합니다.
            * @param[in] StovePCTermsOption* options API에 대한 옵션을 전달하는 구조체입니다
            * @param[in] OnFetchTermsAgreementFinished onFinished 필수 약관 동의에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * @param[in] OnIAPPopupDestroyFinished onDestroy 팝업이 닫힐 경우에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Check whether the user has agreed to the required terms.
            * @param[in] StovePCTermsOption* options Structure that passes options for the API
            * @param[in] OnFetchTermsAgreementFinished onFinished Callback function that registers information about the required terms agreement
            * @param[in] OnIAPPopupDestroyFinished onDestroy Callback function to receive the result when the popup is closed
            * \endenglish
            */
            void IAP_FetchTermsAgreementEx(const StovePCTermsOption* options, OnFetchTermsAgreementFinished onFinished, OnIAPPopupDestroyFinished onDestroy);

            /*!
            * \korean
            * @brief 1회성 결제를 시작하기 위한 결제 URL 을 전달받거나 WebView2를 이용하여 결제를 시작합니다.
            * @param[in] StovePCPaymentOption* options API에 대한 옵션을 전달하는 구조체입니다
            * @param[in] OnStartPaymentFinished onFinished 1회성 결제에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Receive the payment URL to start one-time payment or start the payment using WebView2.
            * @param[in] StovePCPaymentOption* options Structure that passes options for the API
            * @param[in] OnStartPaymentFinished onFinished Callback function that registers information about one-time payment
            * \endenglish
            */
            void IAP_StartPayment(const StovePCPaymentOption* options, OnStartPaymentFinished onFinished);

            /*!
            * \korean
            * @brief 1회성 결제를 시작하기 위한 결제 URL 을 전달받거나 WebView2를 이용하여 결제를 시작합니다.
            * @param[in] StovePCPaymentOption* options API에 대한 옵션을 전달하는 구조체입니다
            * @param[in] OnStartPaymentFinished onFinished 1회성 결제에 대한 정보를 등록한 Callback 함수에 넘겨줍니다
            * @param[in] OnIAPPopupDestroyFinished onDestroy 팝업이 닫힐 경우에 대한 결과를 넘겨받는 Callback 함수
            * \endkorean
            * \english
            * @brief Receive the payment URL to start one-time payment or start the payment using WebView2.
            * @param[in] StovePCPaymentOption* options Structure that passes options for the API
            * @param[in] OnStartPaymentFinished onFinished Callback function that registers information about one-time payment
            * @param[in] OnIAPPopupDestroyFinished onDestroy Callback function to receive the result when the popup is closed
            * \endenglish
            */
            void IAP_StartPaymentEx(const StovePCPaymentOption* options, OnStartPaymentFinished onFinished, OnIAPPopupDestroyFinished onDestroy);

            /*!
            * \korean
            * @brief 현재 사용자가 환불 처리한 구매 기록 목록을 조회합니다.
            * @param[in] OnFetchVoidedPurchasesFinished onFinished 현재 사용자가 환불 처리한 구매 기록 목록 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Retrieve a list of purchase records that the current user has refunded.
            * @param[in] OnFetchVoidedPurchasesFinished onFinished Callback function that registers information about the list of purchase records that the current user has refunded
            * \endenglish
            */
            void IAP_FetchVoidedPurchases(OnFetchVoidedPurchasesFinished onFinished);

            /*!
            * \korean
            * @brief 현재 사용자가 환불 처리한 구매 기록 목록을 조회합니다.
            * @param[in] StovePCVoidedPurchasesMarketType marketType 조회할 마켓 타입
            * @param[in] OnFetchVoidedPurchasesExFinished onFinished 현재 사용자가 환불 처리한 구매 기록 목록 정보를 등록한 Callback 함수에 넘겨줍니다
            * \endkorean
            * \english
            * @brief Retrieve a list of purchase records that the current user has refunded.
            * @param[in] StovePCVoidedPurchasesMarketType marketType Market type to query
            * @param[in] OnFetchVoidedPurchasesExFinished onFinished Callback function that registers information about the list of purchase records that the current user has refunded
            * \endenglish
            */
            void IAP_FetchVoidedPurchasesEx(StovePCVoidedPurchasesMarketType marketType, OnFetchVoidedPurchasesExFinished onFinished);

            /*!
            * \korean
            * @brief IAP SDK를 통해 열린 모든 팝업을 닫습니다.
            * @return struct Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Close all popups opened through the IAP SDK.
            * @return struct Result function call result
            * \endenglish
            */
            Result IAP_CloseAllPopups();

            /*!
            * \korean
            * @brief WebView를 이용하여 WithdrawGame (게임 탈퇴) 팝업을 실행합니다.
            * @param[in] StovePCWithdrawGameOption* options API에 대한 옵션을 전달하는 구조체입니다
            * @param[in] OnWithdrawGameFinished onFinished WebView 실행에 대한 결과를 넘겨받는 콜백 함수 포인터, 게임 탈퇴 여부가 포함되어 있습니다.
            * @param[in] OnIAPPopupDestroyFinished onDestroy 팝업을 닫을 시 응답받는 콜백 함수 포인터
            * \endkorean
            * \english
            * @brief Execute the WithdrawGame (game withdrawal) popup using WebView.
            * @param[in] StovePCWithdrawGameOption* options Structure that passes options for the API
            * @param[in] OnWithdrawGameFinished onFinished Callback function pointer to receive the result of WebView execution, including whether to withdraw from the game
            * @param[in] OnIAPPopupDestroyFinished onDestroy Callback function pointer to receive the response when the popup is closed
            * \endenglish
            */
            void IAP_WithdrawGame(const StovePCWithdrawGameOption* options, OnWithdrawGameFinished onFinished, OnIAPPopupDestroyFinished onDestroy);

            /*!
            * \korean
            * @brief IAPSDK의 버전 정보를 조회합니다.
            * @param[out] wchar_t* version 버전 정보
            * @param[in] uint32_t length 배열의 길이
            * @return struct Result 함수 호출 결과
            * \endkorean
            * \english
            * @brief Query the version information of IAPSDK.
            * @param[out] wchar_t* version version information
            * @param[in] uint32_t length length of the array
            * @return struct Result function call result
            * \endenglish
            */
            Result IAP_GetVersion(__out wchar_t* version, uint32_t length);
        }
    }
}