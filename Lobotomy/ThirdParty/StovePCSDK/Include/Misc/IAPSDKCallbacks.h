#pragma once

/*!
    * @file     Callbacks.h
    * \korean
    * @brief    IAPSDK에서 사용하는 Callback 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Callback values used in IAPSDK.
    * \endenglish
*/

#include "IAPSDKStructures.h"

// c style callbacks
namespace Stove
{
    namespace PCSDK
    {
        namespace IAP
        {
            /*!
            * \korean
            * @brief        IAP_FetchShopCategories API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCShopCategory* shopCategorys StovePCShopCategory 배열
            * @param[out]   uint32_t shopCategorySize StovePCShopCategory 배열의 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchShopCategories API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCShopCategory* shopCategorys StovePCShopCategory array
            * @param[out]   uint32_t shopCategorySize Size of StovePCShopCategory array
            * \endenglish
            */
            typedef void(__cdecl* OnFetchShopCategoriesFinished)(CallbackResult callbackResult, StovePCShopCategory* shopCategorys, uint32_t shopCategorySize);

            /*!
            * \korean
            * @brief        IAP_FetchProducts API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCProduct* products StovePCProduct 배열
            * @param[out]   uint32_t productSize StovePCProduct 배열의 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchProducts API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCProduct* products StovePCProduct array
            * @param[out]   uint32_t productSize Size of StovePCProduct array
            * \endenglish
            */
            typedef void(__cdecl* OnFetchProductsFinished)(CallbackResult callbackResult, StovePCProduct* products, uint32_t productSize);

            /*!
            * \korean
            * @brief        IAP_FetchProductsEx API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCProductEx* products StovePCProductEx 배열
            * @param[out]   uint32_t productSize StovePCProductEx 배열의 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchProductsEx API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCProductEx* products StovePCProductEx array
            * @param[out]   uint32_t productSize Size of StovePCProductEx array
            * \endenglish
            */
            typedef void(__cdecl* OnFetchProductsExFinished)(CallbackResult callbackResult, StovePCProductEx* products, uint32_t productSize);

            /*!
            * \korean
            * @brief        IAP_StartPurchase API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]  CallbackResult callbackResult 콜백 결과 값
            * @param[out]  StovePCPurchaseResult purchaseResult StartPurchase 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_StartPurchase API
            * @param[out]  CallbackResult callbackResult Callback result value
            * @param[out]  StovePCPurchaseResult purchaseResult StartPurchase result value
            * \endenglish
            */
            typedef void(__cdecl* OnStartPurchaseFinished)(CallbackResult callbackResult, StovePCPurchaseResult purchaseResult);

            /*!
            * \korean
            * @brief        IAP_ConfirmPurchase API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   bool status 구매 상태
            * @param[out]   StovePCPurchasedProduct* purchasedProducts StovePCPurchasedProduct 배열
            * @param[out]   uint32_t purchasedProductSize StovePCPurchasedProduct 배열 크기
            * @param[out]   StovePCChargeInfo* chargeInfos StovePCChargeInfo 배열
            * @param[out]   uint32_t chargeInfoSize StovePCChargeInfo 배열 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_ConfirmPurchase API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   bool status Purchase status
            * @param[out]   StovePCPurchasedProduct* purchasedProducts StovePCPurchasedProduct array
            * @param[out]   uint32_t purchasedProductSize Size of StovePCPurchasedProduct array
            * @param[out]   StovePCChargeInfo* chargeInfos StovePCChargeInfo array
            * @param[out]   uint32_t chargeInfoSize Size of StovePCChargeInfo array
            * \endenglish
            */
            typedef void(__cdecl* OnConfirmPurchaseFinished)(CallbackResult callbackResult, bool status, StovePCPurchasedProduct* purchasedProducts, uint32_t purchasedProductSize, StovePCChargeInfo* chargeInfos, uint32_t chargeInfoSize);

            /*!
            * \korean
            * @brief        IAP_FetchInventory API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCInventoryItem* inventoryItems StovePCInventoryItem 배열
            * @param[out]   uint32_t inventoryItemSize StovePCInventoryItem 배열 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchInventory API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCInventoryItem* inventoryItems StovePCInventoryItem array
            * @param[out]   uint32_t inventoryItemSize Size of StovePCInventoryItem array
            * \endenglish
            */
            typedef void(__cdecl* OnFetchInventoryFinished)(CallbackResult callbackResult, StovePCInventoryItem* inventoryItems, uint32_t inventoryItemSize);

            /*!
            * \korean
            * @brief        IAP_FetchTermsAgreement API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   bool agreed 이용약관 동의 여부
            * @param[out]   wchar* url 이용약관 url 주소 (agreed == true 이면 빈값)
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchTermsAgreement API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   bool agreed Terms agreement status
            * @param[out]   wchar_t* url Terms agreement url address (if agreed == true, it is empty)
            * \endenglish
            */
            typedef void(__cdecl* OnFetchTermsAgreementFinished)(CallbackResult callbackResult, bool agreed, const wchar_t* url);

            /*!
            * \korean
            * @brief        IAP_StartPayment API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   wchar_t* url 1회용 결제 url 주소
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_StartPayment API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   wchar_t* url One-time payment url address
            * \endenglish
            */
            typedef void(__cdecl* OnStartPaymentFinished)(CallbackResult callbackResult, const wchar_t* url);

            /*!
            * \korean
            * @brief        IAP_FetchVoidedPurchases API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCVoidedPurchase* voidedPurchases StovePCVoidedPurchase 배열
            * @param[out]   uint32_t voidedPurchaseSize StovePCVoidedPurchase 배열 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchVoidedPurchases API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCVoidedPurchase* voidedPurchases StovePCVoidedPurchase array
            * @param[out]   uint32_t voidedPurchaseSize Size of StovePCVoidedPurchase array
            * \endenglish
            */
            typedef void(__cdecl* OnFetchVoidedPurchasesFinished)(CallbackResult callbackResult, StovePCVoidedPurchase* voidedPurchases, uint32_t voidedPurchaseSize);

            /*!
            * \korean
            * @brief        IAP_FetchVoidedPurchasesEx API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   StovePCVoidedPurchasesEx* voidedPurchasesEx StovePCVoidedPurchasesEx 배열
            * @param[out]   uint32_t voidedPurchaseSize StovePCVoidedPurchasesEx 배열 크기
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_FetchVoidedPurchasesEx API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   StovePCVoidedPurchasesEx* voidedPurchasesEx StovePCVoidedPurchasesEx array
            * @param[out]   uint32_t voidedPurchaseSize Size of StovePCVoidedPurchasesEx array
            * \endenglish
            */
            typedef void(__cdecl* OnFetchVoidedPurchasesExFinished)(CallbackResult callbackResult, StovePCVoidedPurchasesEx* voidedPurchasesEx, uint32_t voidedPurchaseSize);


            /*!
            * \korean
            * @brief        IAP SDK 웹뷰 팝업을 닫을 시 응답 받는 콜백 함수 포인터
                            콜백은 IAPSDK를 통해 생성된 팝업이 모두 닫혀야 호출됩니다.
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * \endkorean
            * \english
            * @brief        Callback function pointer received when closing the IAP SDK webview popup.
                            The callback must be called after all popups created through IAPSDK are closed.
            * @param[out]   CallbackResult callbackResult Callback result value
            * \endenglish
            */
            typedef void(__cdecl* OnIAPPopupDestroyFinished)(CallbackResult callbackResult);


            /*!
            * \korean
            * @brief        IAP_WithdrawGame API 호출 시 응답받는 콜백 함수 포인터
            * @param[out]   CallbackResult callbackResult 콜백 결과 값
            * @param[out]   bool gameWithdrawal 게임 해지 여부
            * \endkorean
            * \english
            * @brief        Callback function pointer received when calling the IAP_WithdrawGame API
            * @param[out]   CallbackResult callbackResult Callback result value
            * @param[out]   bool gameWithdrawal Game withdrawal result
            * \endenglish
            */
            typedef void(__cdecl* OnWithdrawGameFinished)(CallbackResult callbackResult, bool gameWithdrawal);
        }
    }
}