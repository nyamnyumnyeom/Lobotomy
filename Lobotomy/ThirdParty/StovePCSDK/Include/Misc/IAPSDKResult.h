#pragma once

/*!
    * @file     IAPSDKResult.h
    * \korean
    * @brief    IAPSDK에서 사용하는 Code값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Code values used in IAPSDK.
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
            * @file     IAPSDKResult.h
            * \korean
            * @brief    IAPSDK에서 사용하는 함수들의 Code
            * \endkorean
            * \english
            * @brief    Code of functions used in IAPSDK
            * \endenglish
            */
            enum class SDKMethod : uint32_t
            {
                /*
                * Common Method
                */
                /// 1 : IAP_Initialize
                INITIALIZE = 1U,

                /// 2 : IAP_UnInitialize
                UNINITIALIZE = 2U,

                /// 3 : Internal method (Deprecated)
                INTERNAL_SEND_81PLUG = 3U,

                /// 4 : Internal method (Deprecated)
                INTERNAL_UPDATE_81PLUG = 4U,

                /// 5 : IAP_GetVersion
                GET_VERSION = 5U,

                /*
                * IAPSDK Method
                */
                /// 80 : IAP_FetchShopCategories
                FETCH_SHOP_CATEGORIES = 80U,

                /// 81 : IAP_FetchProducts
                FETCH_PRODUCTS = 81U,

                /// 82 : IAP_StartPurchase
                START_PURCHASE = 82U,

                /// 83 : IAP_ConfirmPurchase
                CONFIRM_PURCHASE = 83U,

                /// 84 : IAP_FetchInventory
                FETCH_INVENTORY = 84U,

                /// 85 : IAP_FetchTermsAgreement
                FETCH_TERMS_AGREEMENT = 85U,

                /// 86 : IAP_StartPayment
                START_PAYMENT = 86U,

                /// 87 : IAP_FetchVoidedPurchases
                FETCH_VOIDED_PURCHASES = 87U,

                /// 88 : IAP_CloseAllPopups
                CLOSE_ALL_POPUPS = 88U,

                /// 89 : IAP_WithdrawGame
                WITHDRAW_GAME = 89U,
            };

            /*!
            * @file     IAPSDKResult.h
            * \korean
            * @brief    IAPSDK에서 사용하는 함수의 Result Code
            * \endkorean
            * \english
            * @brief    Result Code of functions used in IAPSDK
            * \endenglish
            */
            enum class SDKResultCode : uint32_t
            {
                /*
                * Common Result
                */

                /*!
                * \korean
                * 0 : 성공
                * \endkorean
                * \english
                * 0 : Success
                * \endenglish
                */
                SUCCESS = 0U,

                /*!
                * \korean
                * 1 : 실패
                * \endkorean
                * \english
                * 1 : Fail
                * \endenglish
                */
                FAIL = 1U,

                /*!
                * \korean
                * 2 : Config 파일을 찾을 수 없습니다.
                * \endkorean
                * \english
                * 2 : Config file not found.
                * \endenglish
                */
                INVALID_CONFIG = 2U,

                /*!
                * \korean
                * 3 : 로그 레벨의 값이 유효하지 않습니다.
                * \endkorean
                * \english
                * 3 : The log level value is invalid.
                * \endenglish
                */
                INVALID_LOG_LEVEL = 3U,

                /*!
                * \korean
                * 4 : 로그 경로가 유효하지 않습니다.
                * \endkorean
                * \english
                * 4 : Invalid log path.
                * \endenglish
                */
                INVALID_LOG_PATH = 4U,

                /*!
                * \korean
                * 5 : 잘못된 매개변수가 입력되었습니다.
                * \endkorean
                * \english
                * 5 : Invalid parameter entered.
                * \endenglish
                */
                INVALID_PARAM = 5U,

                /*!
                * \korean
                * 6 : 해당 내용은 구현되지 않았습니다.
                * \endkorean
                * \english
                * 6 : The content has not been implemented.
                * \endenglish
                */
                BASE_NOT_INITIALIZED = 16U,

                /*!
                * \korean
                * 7 : 초기화가 되지 않았습니다.
                * \endkorean
                * \english
                * 7 : Initialization has not been done.
                * \endenglish
                */
                NOT_INITIALIZED = 17U,

                /*!
                * \korean
                * 8 : 이미 초기화가 되었습니다.
                * \endkorean
                * \english
                * 8 : Already initialized.
                * \endenglish
                */
                ALREADY_INITIALIZED = 18U,

                /*!
                * \korean
                * 19 : AccessToken을 찾을 수 없습니다.
                * \endkorean
                * \english
                * 19 : AccessToken cannot be found.
                * \endenglish
                */
                INVALID_ACCESS_TOKEN = 19U,

                /*!
                * \korean
                * 20 : Token 객체를 찾을 수 없습니다.
                * \endkorean
                * \english
                * 20 : Token object not found.
                * \endenglish
                */
                NULL_TOKEN_ENTITY = 20U,

                /*!
                * \korean
                * 21 : 현재 객체를 찾을 수 없습니다.
                * \endkorean
                * \english
                * 21 : Unable to find the current object.
                * \endenglish
                */
                NULL_ENTITY = 21U,

                /*!
                * \korean
                * 22 : Http 통신 에러가 발생했습니다.
                * \endkorean
                * \english
                * 22 : Http communication error occurred.
                * \endenglish
                */
                HTTP_ERROR = 22U,

                /*!
                * \korean
                * 23 : Http API Response 에러가 발생했습니다.
                * \endkorean
                * \english
                * 23 : Http API Response error occurred.
                * \endenglish
                */
                RESPONSE_ERROR = 23U,

                /*!
                * \korean
                * 24 : Http API Response Code를 찾을 수 없습니다.
                * \endkorean
                * \english
                * 24 : Unable to find Http API Response Code.
                * \endenglish
                */
                RESPONSE_INVALID_CODE = 24U,

                /*!
                * \korean
                * 25 : Http API Response 값이 비어있습니다.
                * \endkorean
                * \english
                * 25 : Http API Response value is empty.
                * \endenglish
                */
                RESPONSE_VALUE_IS_NULL = 25U,

                /*!
                * \korean
                * 26 : Http API Response 포멧이 틀립니다.
                * \endkorean
                * \english
                * 26 : Http API Response format is incorrect.
                * \endenglish
                */
                RESPONSE_INVALID_VALUE_FORMAT = 26U,

                /*!
                * \korean
                * 27 : 81 Plug 전송을 실패했습니다. (Deprecated)
                * \endkorean
                * \english
                * 27 : 81 Plug transmission failed. (Deprecated)
                * \endenglish
                */
                LOG_81PLUG_ERROR = 27U,

                /*!
                * \korean
                * 28 : 81 Plug 업데이트를 실패했습니다. (Deprecated)
                * \endkorean
                * \english
                * 28 : 81 Plug update failed. (Deprecated)
                * \endenglish
                */
                UPDATE_81PLUG_FEED_ERROR = 28U,

                /*
                * \korean
                * 29 : 현재 비동기 작업이 진행중입니다.
                * \endkorean
                * \english
                * 29 : The current asynchronous operation is in progress.
                * \endenglish
                */
                ASYNC_OPERATION_IN_PROGRESS = 29U,

                /*!
                * \korean
                * 30 : BaseSDK를 Uninitialize하였습니다.
                * \endkorean
                * \english
                * 30 : BaseSDK has been Uninitialized.
                * \endenglish
                */
                BASE_UNINITIALIZED = 30U,

                /*!
                * \korean
                * 31 : 현재 국가에서는 지원되지 않는 기능입니다.
                * \endkorean
                * \english
                * 31 : This feature is not supported in the current country
                * \endenglish
                */
                NOT_SUPPORTED_COUNTRY = 31,

                /*!
                * \korean
                * 251 : PC SDK DLL을 찾지 못했습니다.
                * \endkorean
                * \english
                * 251 : PC SDK DLL not found.
                * \endenglish
                */
                PCSDK_DLL_NOT_FOUND = 251U,

                /*!
                * \korean
                * 252 : 해당 내용은 구현되지 않았습니다.
                * \endkorean
                * \english
                * 252 : The content has not been implemented.
                * \endenglish
                */
                NOT_IMPLEMENTED = 252U,

                /*!
                * \korean
                * 253 : 관리되지 않는 예외가 발생하였습니다.
                * \endkorean
                * \english
                * 253 : An unmanaged exception occurred.
                * \endenglish
                */
                UNMANAGED_EXCEPTION = 253U,

                /*!
                * \korean
                * 254 : 관리되는 예외가 발생하였습니다.
                * \endkorean
                * \english
                * 254 : A managed exception occurred.
                * \endenglish
                */
                MANAGED_EXCEPTION = 254U,

                /*!
                * \korean
                * 255 : 알 수 없는 에러가 발생하였습니다.
                * \endkorean
                * \english
                * 255 : An unknown error occurred.
                * \endenglish
                */
                UNKNOWN_ERROR = 255U,

                /*
                * IAPSDK Result
                */

                /*!
                * \korean
                * 80 : ViewUI가 초기화되지 않았습니다.
                * \endkorean
                * \english
                * 80 : ViewUI has not been initialized.
                * \endenglish
                */
                VIEWUI_NOT_INITIALIZED = 80U,

                /*!
                * \korean
                * 81 : ViewUI 정리에 실패했습니다.
                * \endkorean
                * \english
                * 81 : ViewUI cleanup failed.
                * \endenglish
                */
                VIEWUI_UNINIT_FAILED = 81U,

                /*!
                * \korean
                * 82 : Webview가 초기화되지 않았습니다.
                * \endkorean
                * \english
                * 82 : Webview has not been initialized.
                * \endenglish
                */
                WEBVIEW_CREATE_FAIL = 82U,

                /*!
                * \korean
                * 83 : URL 불러오기를 실패하였습니다.
                * \endkorean
                * \english
                * 83 : URL loading failed.
                * \endenglish
                */
                WEBVIEW_LOAD_URL_FAIL = 83U,

                /*!
                * \korean
                * 84 : StartPurchase API 실행 도중 아이템 구매가 완료되지 않은 채 Webview가 종료되었습니다 (WITH_WEBVIEW_AND_CONFIRM_RESULT 옵션 한정).
                * \endkorean
                * \english
                * 84 : StartPurchase API execution failed because the item purchase was not completed and the Webview was closed (limited to WITH_WEBVIEW_AND_CONFIRM_RESULT option).
                * \endenglish
                */
                WEBVIEW_CLOSED_BEFORE_PURCHASE = 84U,

                /*!
                * \korean
                * 85 : StartPurchase API 매개변수의 길이 제한을 초과했습니다(serviceTxnNo는 50자, extraData는 500자 제한).
                * \endkorean
                * \english
                * 85 : StartPurchase API parameter length exceeded (serviceTxnNo is limited to 50 characters, extraData is limited to 500 characters).
                * \endenglish
                */
                PARAMETER_LENGTH_EXCEEDED = 85U,

                /*!
                * \korean
                * 86 : 문자열이 JSON 형식이 아닙니다.
                * \endkorean
                * \english
                * 86 : The string is not in JSON format.
                * endenglish
                */
                INVALID_JSON_STRING = 86U,

                /*!
                * \korean
                * 87 : Cookie 생성에 실패했습니다.
                * \endkorean
                * \english
                * 87 : Cookie creation failed.
                * \endenglish
                */
                WEBVIEW_CREATE_COOKIE_FAIL = 87U,

                /*!
                * \korean
                * 88 : 구매하려는 상품의 금액이나 갯수가 유효한 값이 아닙니다.
                * \endkorean
                * \english
                * 88 : The amount or quantity of the product to be purchased is not a valid value.
                * \endenglish
                */
                INVALID_ORDER_PRODUCT_INFORMATION = 88U,

                /*!
                * \korean
                * 89 : Webview 일괄 닫기에 실패했습니다.
                * \endkorean
                * \english
                * 89 : Webview batch close failed.
                * \endenglish
                */
                WEBVIEW_CLOSE_ALL_FAIL = 89U,

                /*!
                * \korean
                * 90 : Webview 닫기에 실패했습니다.
                * \endkorean
                * \english
                * 90 : Webview batch close failed.
                * \endenglish
                */
                WEBVIEW_CLOSE_FAIL = 90U,
            };

            /*!
            * @file     IAPSDKResult.h
            * \korean
            * @brief    IAPSDK의 이름
            * \endkorean
            * \english
            * @brief    Name of IAPSDK
            * \endenglish
            */
            static const wchar_t* IAPSDKName = L"IAPSDK";
        }
    }
}
