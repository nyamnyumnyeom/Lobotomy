#pragma once

/*!
    * @file     Structures.h
    * \korean
    * @brief    IAPSDK에서 사용하는 Structures 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Structures values used in IAPSDK.
    * \endenglish
*/


#include <string>

#include "Misc/BaseSDKEnumerations.h"
#include "Misc/BaseSDKStructures.h"

#include "IAPSDKEnumerations.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace IAP
        {
            // Forward declaration
            struct StovePCShopCategoryCpp;
            struct StovePCFetchProductParamCpp;
            struct StovePCProductCpp;
            struct StovePCProductExCpp;
            struct StovePCOrderProductCpp;
            struct StovePCPurchaseOptionCpp;
            struct StovePCStartPurchaseParamCpp;
            struct StovePCPurchasedProductCpp;
            struct StovePCChargeInfoCpp;
            struct StovePCPurchaseResultCpp;
            struct StovePCInventoryItemCpp;
            struct StovePCTermsOptionCpp;
            struct StovePCPaymentOptionCpp;
            struct StovePCVoidedPurchaseCpp;
            struct StovePCVoidedPurchasesExCpp;
            struct StovePCWithdrawGameOptionCpp;

            /*!
            * @struct StovePCShopCategory
            * \korean
            * @brief 개별 카테고리 정보를 전달합니다. IAP_FetchShopCategories 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief Delivers individual category information. Used when delivering results in the IAP_FetchShopCategories callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCShopCategory
            {
            public:
                /*!
                * \korean
                * @brief    카테고리 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category ID.
                * \endenglish
                * @return   const wchar_t* categoryId
                */
                const wchar_t* GetCategoryId() const;

                /*!
                * \korean
                * @brief    부모 카테고리 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the parent category ID.
                * \endenglish
                * @return   const wchar_t* parentCategoryId
                */
                const wchar_t* GetParentCategoryId() const;

                /*!
                * \korean
                * @brief    카테고리 순서를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category order.
                * \endenglish
                * @return   int32_t displayNumber
                */
                int32_t GetDisplayNumber() const;

                /*!
                * \korean
                * @brief    카테고리명을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category name.
                * \endenglish
                * @return   const wchar_t* name
                */
                const wchar_t* GetName() const;

                /*!
                * \korean
                * @brief    계층 구조상의 깊이를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the depth in the hierarchy.
                * \endenglish
                * @return   int32_t depth
                */
                int32_t GetDepth() const;

            public:
                StovePCShopCategory();
                StovePCShopCategory(const StovePCShopCategory& rhs);
                StovePCShopCategory(const StovePCShopCategoryCpp* rhs);
                ~StovePCShopCategory();

                StovePCShopCategory& operator=(const StovePCShopCategory& rhs);
                StovePCShopCategory& operator=(const StovePCShopCategoryCpp* rhs);

            private:
                void DeepCopy(const StovePCShopCategory& rhs);
                void DeepCopy(const StovePCShopCategoryCpp* rhs);


            private:
                /*!
                * \korean
                * @brief    카테고리 아이디
                * \endkorean
                * \english
                * @brief    Category ID
                * \endenglish
                */
                wchar_t* categoryId = nullptr;

                /*!
                * \korean
                * @brief    부모 카테고리 아이디
                * \endkorean
                * \english
                * @brief    Parent category ID
                * \endenglish
                */
                wchar_t* parentCategoryId = nullptr;

                /*!
                * \korean
                * @brief    카테고리 순서
                * \endkorean
                * \english
                * @brief    Category order
                * \endenglish
                */
                int32_t displayNumber;

                /*!
                * \korean
                * @brief    카테고리명
                * \endkorean
                * \english
                * @brief    Category name
                * \endenglish
                */
                wchar_t* name = nullptr;

                /*!
                * \korean
                * @brief    계층 구조상의 깊이
                * \endkorean
                * \english
                * @brief    Depth in the hierarchy
                * \endenglish
                */
                int32_t depth;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCFetchProductParam
            * \korean
            * @brief IAP_FetchProducts API 실행 시 전달할 값을 담는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that contains the values to be passed when executing the IAP_FetchProducts API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCFetchProductParam
            {
            public:
                /*!
                * \korean
                * @brief    카테고리 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category ID.
                * \endenglish
                * @return   const wchar_t* categoryId
                */
                const wchar_t* GetCategoryId() const;

                /*!
                * \korean
                * @brief    카테고리 아이디를 설정합니다.
                * @details  전달 되지 않을 경우 전체 카테고리에 대한 아이템 리스트 리턴합니다.
                * \endkorean
                * \english
                * @brief    Set the category ID.
                * @details  If not passed, it returns a list of items for the entire category.
                * \endenglish
                * @param    const wchar_t* categoryId
                */
                void SetCategoryId(const wchar_t* categoryId);

                /*!
                * \korean
                * @brief    상품 정보 조회 시 페이지 번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the page number when fetching product information.
                * \endenglish
                * @return   int32_t pageNumber
                */
                int32_t GetPageNumber() const;

                /*!
                * \korean
                * @brief    상품 정보 조회 시 페이지 번호를 설정합니다.
                * @details  전달 되지 않을 경우 기본 1로 세팅됩니다.
                * \endkorean
                * \english
                * @brief    Set the page number when fetching product information.
                * @details  If not passed, it is set to the default 1.
                * \endenglish
                * @param    int32_t pageNumber
                */
                void SetPageNumber(int32_t number);

                /*!
                * \korean
                * @brief    상품 정보 조회 시 페이지 크기를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the page size when fetching product information.
                * \endenglish
                * @return   int32_t pageSize
                */
                int32_t GetPageSize() const;

                /*!
                * \korean
                * @brief    상품 정보 조회 시 페이지 크기를 설정합니다.
                * @details  전달 되지 않을 경우 기본 20로 세팅
                            등록 된 전체 상품을 조회 하고 싶을 경우 page_no: 1, page_size: Int 최대 값(2,147,483,647) 이하로 세팅
                * \endkorean
                * \english
                * @brief    Set the page size when fetching product information.
                * @details  If not passed, it is set to the default 20.
                            If you want to view all registered products, set page_no: 1, page_size: Int maximum value (less than 2,147,483,647)
                * @param    int32_t pageSize
                */
                void SetPageSize(int32_t size);

            public:
                StovePCFetchProductParam();
                StovePCFetchProductParam(const StovePCFetchProductParam& rhs);
                StovePCFetchProductParam(const StovePCFetchProductParamCpp* rhs);
                ~StovePCFetchProductParam();

                StovePCFetchProductParam& operator=(const StovePCFetchProductParam& rhs);
                StovePCFetchProductParam& operator=(const StovePCFetchProductParamCpp* rhs);

            private:
                void DeepCopy(const StovePCFetchProductParam& rhs);
                void DeepCopy(const StovePCFetchProductParamCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    카테고리 아이디
                * @details  빈 값이면 전체 상품 목록을 조회
                * \endkorean
                * \english
                * @brief    Category ID
                * @details  if empty, it retrieves the entire product list
                * \endenglish
                */
                wchar_t* categoryId = nullptr;

                /*!
                * \korean
                * @brief    상품 정보 조회 시 페이지 번호
                * \endkorean
                * \english
                * @brief    Page number when fetching product information
                * \endenglish
                */
                int32_t pageNumber;

                /*!
                * \korean
                * @brief    상품 정보 조회 시 페이지 크기
                * \endkorean
                * \english
                * @brief    Page size when fetching product information
                * \endenglish
                */
                int32_t pageSize;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCProduct
            * \korean
            * @brief 개별 상품 정보를 전달하는 구조체입니다. IAP_FetchProducts 콜백에 결과 전달 시 사용됩니다.
            * \endkorean
            * \english
            * @brief A structure that delivers individual product information. Used when delivering results in the IAP_FetchProducts callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCProduct
            {
            public:
                /*!
                * \korean
                * @brief    플랫폼 상품 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the platform product ID.
                * \endenglish
                * @return   int64_t productId
                */
                int64_t GetProductId() const;

                /*!
                * \korean
                * @brief    상품 아이디에 매핑되는 게임 내 아이템 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game item ID mapped to the product ID.
                * \endenglish
                * @return   const wchar_t* gameItemId
                */
                const wchar_t* GetGameItemId() const;

                /*!
                * \korean
                * @brief    상품명을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product name.
                * \endenglish
                * @return   const wchar_t* name
                */
                const wchar_t* GetName() const;

                /*!
                * \korean
                * @brief    상품 상세를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product details.
                * \endenglish
                * @return   const wchar_t* description
                */
                const wchar_t* GetDescription() const;

                /*!
                * \korean
                * @brief    개별 상품 수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the individual product quantity.
                * \endenglish
                * @return   const wchar_t* quantity
                */
                int32_t GetQuantity() const;

                /*!
                * \korean
                * @brief    아이템 유형 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the item type code.
                * \endenglish
                * @return   ProductTypeCode productTypeCode
                */
                ProductTypeCode GetProductTypeCode() const;

                /*!
                * \korean
                * @brief    카테고리 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category ID.
                * \endenglish
                * @return   const wchar_t* categoryId
                */
                const wchar_t* GetCategoryId() const;

                /*!
                * \korean
                * @brief    카테고리 이름을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category name.
                * \endenglish
                * @return   const wchar_t* categoryName
                */
                const wchar_t* GetCategoryName() const;

                /*!
                * \korean
                * @brief    통화 코드를 가져옵니다.
                * @details  상품 가격 표시에 사용 합니다.
                * \endkorean
                * \english
                * @brief    Get the currency code.
                * @details  Used to display product prices.
                * \endenglish
                * @return   const wchar_t* currencyCode
                */
                const wchar_t* GetCurrencyCode() const;

                /*!
                * \korean
                * @brief    상품 정가(결제)를 가져옵니다.
                * @details  상품의 정가 가격 표시에만 사용하세요.
                * \endkorean
                * \english
                * @brief    Get the product price (payment).
                * @details  Use only for displaying the regular price of the product.
                * \endenglish
                * @return   double price
                */
                double GetPrice() const;

                /*!
                * \korean
                * @brief    상품 정가(전시)를 가져옵니다.
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Get the product price (display).
                * @details  Currently not in use
                * \endenglish
                * @return   double displayPrice
                */
                double GetDisplayPrice() const;

                /*!
                * \korean
                * @brief    상품 정가 문자열(전시)을 가져옵니다.
                * @details  정가 가격 표시에만 사용하세요.
                * \endkorean
                * \english
                * @brief    Get the product price string (display).
                * @details  Use only for displaying the regular price.
                * \endenglish
                * @return   const wchar_t* displayPriceString
                */
                const wchar_t* GetDisplayPriceString() const;

                /*!
                * \korean
                * @brief    상품 판매가(결제)를 가져옵니다.
                * @details  상점에 실제 판매가를 표시할때와 상품 구매 요청시 전달하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Get the product sale price (payment).
                * @details  Used when displaying the actual sale price in the store and when requesting product purchase.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * @return   double salePrice
                */
                double GetSalePrice() const;

                /*!
                * \korean
                * @brief    상품 판매가(전시)를 가져옵니다.
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Get the product sale price (display).
                * @details  Currently not in use
                * \endenglish
                * @return   double displaySalePrice
                */
                double GetDisplaySalePrice() const;

                /*!
                * \korean
                * @brief    상품 판매가 문자열(전시)을 가져옵니다.
                * @details  상점에 통화기호가 포함된 실제 판매가를 표시할때 사용하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Get the product sale price string (display).
                * @details  Used when displaying the actual sale price including the currency symbol in the store.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * \endenglish
                * @return   const wchar_t* displaySalePriceString
                */
                const wchar_t* GetDisplaySalePriceString() const;

                /*!
                * \korean
                * @brief    할인 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get if there is a discount.
                * \endenglish
                * @return   bool isDiscount
                */
                bool IsDiscount() const;

                /*!
                * \korean
                * @brief    할인 유형을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount type.
                * \endenglish
                * @return   DiscountType discountType
                */
                DiscountType GetDiscountType() const;

                /*!
                * \korean
                * @brief    할인 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount value.
                * \endenglish
                * @return   int32_t discountTypeValue
                */
                int32_t GetDiscountTypeValue() const;

                /*!
                * \korean
                * @brief    할인 시작 일자(epoch time milliseconds)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount start date (epoch time milliseconds).
                * \endenglish
                * @return   int64_t discountBeginDate
                */
                int64_t GetDiscountBeginDate() const;

                /*!
                * \korean
                * @brief    할인 종료 일자(epoch time milliseconds)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount end date (epoch time milliseconds).
                * \endenglish
                * @return   int64_t discountEndDate
                */
                int64_t GetDiscountEndDate() const;

                /*!
                * \korean
                * @brief    상품 총 판매수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the total quantity of product sales.
                * \endenglish
                * @return   int32_t totalQuantity
                */
                int32_t GetTotalQuantity() const;

                /*!
                * \korean
                * @brief    회원 구매 수량을 가져옵니다.
                * @details  로그인 한 계정 별 구매 수량입니다.
                * \endkorean
                * \english
                * @brief    Get the member purchase quantity.
                * @details  Purchase quantity per logged-in account.
                * \endenglish
                * @return   int32_t memberQuantity
                */
                int32_t GetMemberQuantity() const;

                /*!
                * \korean
                * @brief    guid 구매 수량을 가져옵니다.
                * @details  게임의 Unique 한 계정 별 구매 수량입니다.
                * \endkorean
                * \english
                * @brief    Get the guid purchase quantity.
                * @details  Purchase quantity per unique account in the game.
                * \endenglish
                * @return   int32_t guidQuantity
                */
                int32_t GetGuidQuantity() const;

                /*!
                * \korean
                * @brief    대표 상품 이미지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the representative product image.
                * \endenglish
                * @return   const wchar_t* thumbnailUrl
                */
                const wchar_t* GetThumbnailUrl() const;

                /*!
                * \korean
                * @brief    청약 철회 가능 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get if withdrawal is possible.
                * \endenglish
                * @return   bool canWithdraw
                */
                bool CanWithdraw() const;

                /*!
                * \korean
                * @brief    구매 여부 (구매 이력이 한 건 이상인 경우 true)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the purchase status (true if there is at least one purchase history).
                * \endenglish
                * @return   bool purchasedAtLeastOnce
                */
                bool GetPurchasedAtLeastOnce() const;

                /*!
                * \korean
                * @brief    구매 여부 (구매 이력이 한 건 이상인 경우 true)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the purchase status (true if there is at least one purchase history).
                * \endenglish
                * @return   PurchaseLimitTypeCode purchaseLimitTypeCode
                */
                PurchaseLimitTypeCode GetPurchaseLimitTypeCode() const;

                /*!
                * \korean
                * @brief    판매 제한 수량을 가져옵니다.
                * @details  GetPurchaseLimitTypeCode() 값이 PurchaseLimitTypeCode::CHARACTER 일 경우 회원 별 제한 수량
                * \endkorean
                * \english
                * @brief    Get the sale limit quantity.
                * @details  If the value of GetPurchaseLimitTypeCode() is PurchaseLimitTypeCode::CHARACTER, it is the limit quantity per member.
                * \endenglish
                * @return   int32_t purchaseLimitCount
                */
                int32_t GetPurchaseLimitCount() const;

                /*!
                * \korean
                * @brief    총 판매 제한 수량 (0일 경우 무제한)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the total sale limit quantity (0 for unlimited).
                * \endenglish
                * @return   int32_t saleLimitCount
                */
                int32_t GetSaleLimitCount() const;

                /*!
                * \korean
                * @brief    판매 시작 일자(epoch time milliseconds)를 가져옵니다.
                * @details  판매 기간이 상시 일 경우 null(SDK: 0) 리턴
                * \endkorean
                * \english
                * @brief    Get the sale start date (epoch time milliseconds).
                * @details  If the sale period is all day, return null (SDK: 0).
                * \endenglish
                * @return   int64_t saleBeginDate
                */
                int64_t GetSaleBeginDate() const;

                /*!
                * \korean
                * @brief    판매 종료 일자(epoch time milliseconds)를 가져옵니다.
                * @details  판매 기간이 상시 일 경우 null(SDK: 0) 리턴
                * \endkorean
                * \english
                * @brief    Get the sale end date (epoch time milliseconds).
                * @details  If the sale period is all day, return null (SDK: 0).
                * \endenglish
                * @return   int64_t saleEndDate
                */
                int64_t GetSaleEndDate() const;

            public:
                StovePCProduct();
                StovePCProduct(const StovePCProduct& rhs);
                StovePCProduct(const StovePCProductCpp* rhs);
                ~StovePCProduct();

                StovePCProduct& operator=(const StovePCProduct& rhs);
                StovePCProduct& operator=(const StovePCProductCpp* rhs);

            private:
                void DeepCopy(const StovePCProduct& rhs);
                void DeepCopy(const StovePCProductCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    플랫폼 상품 아이디
                * \endkorean
                * \english
                * @brief    Platform product ID
                * \endenglish
                */
                int64_t productId;

                /*!
                * \korean
                * @brief    상품 아이디에 매핑되는 게임 내 아이템 아이디
                * \endkorean
                * \english
                * @brief    Game item ID mapped to the product ID
                * \endenglish
                */
                wchar_t* gameItemId = nullptr;

                /*!
                * \korean
                * @brief    상품명
                * \endkorean
                * \english
                * @brief    Product name
                * \endenglish
                */
                wchar_t* name = nullptr;

                /*!
                * \korean
                * @brief    상품 상세
                * \endkorean
                * \english
                * @brief    Product details
                * \endenglish
                */
                wchar_t* description = nullptr;

                /*!
                * \korean
                * @brief    개별 상품 수량
                * \endkorean
                * \english
                * @brief    Individual product quantity
                * \endenglish
                */
                int32_t quantity;

                /*!
                * \korean
                * @brief    아이템 유형 코드
                * \endkorean
                * \english
                * @brief    Item type code
                * \endenglish
                */
                ProductTypeCode productTypeCode;

                /*!
                * \korean
                * @brief    카테고리 아이디
                * \endkorean
                * \english
                * @brief    Category ID
                * \endenglish
                */
                wchar_t* categoryId = nullptr;

                /*!
                * \korean
                * @brief    카테고리 이름
                * \endkorean
                * \english
                * @brief    Category name
                * \endenglish
                */
                wchar_t* categoryName = nullptr;

                /*!
                * \korean
                * @brief    통화 코드
                * @details  상품 가격 표시에 사용
                * \endkorean
                * \english
                * @brief    Currency code
                * @details  Used to display product prices
                * \endenglish
                */
                wchar_t* currencyCode = nullptr;

                /*!
                * \korean
                * @brief    상품 정가(결제)
                * @details  상품의 정가 가격 표시에만 사용하세요
                * \endkorean
                * \english
                * @brief    Product price (payment)
                * @details  Use only for displaying the regular price of the product
                * \endenglish
                */
                double price;

                /*!
                * \korean
                * @brief    상품 정가(전시)
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Product price (display)
                * @details  Currently not in use
                * \endenglish
                */
                double displayPrice;

                /*!
                * \korean
                * @brief    상품 정가 문자열(전시)
                * @details  정가 가격 표시에만 사용하세요
                * \endkorean
                * \english
                * @brief    Product price string (display)
                * @details  Use only for displaying the regular price
                * \endenglish
                */
                wchar_t* displayPriceString = nullptr;

                /*!
                * \korean
                * @brief    상품 판매가(결제)
                * @details  상점에 실제 판매가를 표시할때와 상품 구매 요청시 전달하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Product sale price (payment)
                * @details  Used when displaying the actual sale price in the store and when requesting product purchase.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * \endenglish
                */
                double salePrice;

                /*!
                * \korean
                * @brief    상품 판매가(전시)
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Product sale price (display)
                * @details  Currently not in use
                * \endenglish
                */
                double displaySalePrice;

                /*!
                * \korean
                * @brief    상품 판매가 문자열(전시)
                * @details  상점에 통화기호가 포함된 실제 판매가를 표시할때 사용하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Product sale price string (display)
                * @details  Used when displaying the actual sale price including the currency symbol in the store.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * \endenglish
                */
                wchar_t* displaySalePriceString = nullptr;

                /*!
                * \korean
                * @brief    할인 여부
                * \endkorean
                * \english
                * @brief    Discount availability
                * \endenglish
                */
                bool isDiscount;

                /*!
                * \korean
                * @brief    할인 유형
                * \endkorean
                * \english
                * @brief    Discount type
                * \endenglish
                */
                DiscountType discountType;

                /*!
                * \korean
                * @brief    할인 값
                * \endkorean
                * \english
                * @brief    Discount value
                * \endenglish
                */
                int32_t discountTypeValue;

                /*!
                * \korean
                * @brief    할인 시작 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Discount start date (epoch time milliseconds)
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t discountBeginDate;

                /*!
                * \korean
                * @brief    할인 종료 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Discount end date
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t discountEndDate;

                /*!
                * \korean
                * @brief    상품 총 판매수량
                * \endkorean
                * \english
                * @brief    Total quantity of product sales
                * \endenglish
                */
                int32_t totalQuantity;

                /*!
                * \korean
                * @brief    회원 구매 수량
                * \endkorean
                * \english
                * @brief    Member purchase quantity
                * \endenglish
                */
                int32_t memberQuantity;

                /*!
                * \korean
                * @brief    guid 구매 수량
                * @details  게임의 Unique 한 계정 별 구매 수량입니다.
                * \endkorean
                * \english
                * @brief    guid purchase quantity
                * @details  Purchase quantity per unique account in the game
                * \endenglish
                */
                int32_t guidQuantity;

                /*!
                * \korean
                * @brief    대표 상품 이미지
                * \endkorean
                * \english
                * @brief    Representative product image
                * \endenglish
                */
                wchar_t* thumbnailUrl = nullptr;

                /*!
                * \korean
                * @brief    청약 철회 가능 여부
                * \endkorean
                * \english
                * @brief    Check if withdrawal is possible
                * \endenglish
                */
                bool canWithdraw;

                /*!
                * \korean
                * @brief    구매 여부 (구매 이력이 한 건 이상인 경우 true)
                * \endkorean
                * \english
                * @brief    Check the purchase status (true if there is at least one purchase history)
                * \endenglish
                */
                bool purchasedAtLeastOnce;

                /*!
                * \korean
                * @brief    할인 유형
                * @details  1. 무제한 2. 회원별 3. 캐릭터별
                * \endkorean
                * \english
                * @brief    Discount type
                * @details  1. Unlimited 2. Per member 3. Per character
                * \endenglish
                */
                PurchaseLimitTypeCode purchaseLimitTypeCode;

                /*!
                * \korean
                * @brief    판매 제한 수량
                * @details  GetPurchaseLimitTypeCode() 값이 PurchaseLimitTypeCode::CHARACTER 일 경우 회원 별 제한 수량
                * \endkorean
                * \english
                * @brief    Sale limit quantity
                * @details  If the value of GetPurchaseLimitTypeCode() is PurchaseLimitTypeCode::CHARACTER, it is the limit quantity per member
                * \endenglish
                */
                int32_t purchaseLimitCount;

                /*!
                * \korean
                * @brief    총 판매 제한 수량
                * @details  0일 경우 무제한
                * \endkorean
                * \english
                * @brief    Total sale limit quantity
                * @details  0 for unlimited
                * \endenglish
                */
                int32_t saleLimitCount;

                /*!
                * \korean
                * @brief    판매 시작 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Sale start date
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t saleBeginDate = 0LL;

                /*!
                * \korean
                * @brief    판매 종료 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Sale end date
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t saleEndDate = 0LL;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCProductEx
            * \korean
            * @brief 개별 상품 정보를 전달하는 구조체입니다. IAP_FetchProductsEx 콜백에 결과 전달 시 사용됩니다.
            * \endkorean
            * \english
            * @brief A structure that delivers individual product information. Used when delivering results in the IAP_FetchProductsEx callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCProductEx
            {
            public:
                /*!
                * \korean
                * @brief    플랫폼 상품 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the platform product ID.
                * \endenglish
                * @return   int64_t productId
                */
                int64_t GetProductId() const;

                /*!
                * \korean
                * @brief    상품 아이디에 매핑되는 게임 내 아이템 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game item ID mapped to the product ID.
                * \endenglish
                * @return   const wchar_t* gameItemId
                */
                const wchar_t* GetGameItemId() const;

                /*!
                * \korean
                * @brief    상품명을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product name.
                * \endenglish
                * @return   const wchar_t* name
                */
                const wchar_t* GetName() const;

                /*!
                * \korean
                * @brief    상품 상세를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product details.
                * \endenglish
                * @return   const wchar_t* description
                */
                const wchar_t* GetDescription() const;

                /*!
                * \korean
                * @brief    개별 상품 수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the individual product quantity.
                * \endenglish
                * @return   const wchar_t* quantity
                */
                int32_t GetQuantity() const;

                /*!
                * \korean
                * @brief    아이템 유형 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the item type code.
                * \endenglish
                * @return   ProductTypeCode productTypeCode
                */
                ProductTypeCode GetProductTypeCode() const;

                /*!
                * \korean
                * @brief    카테고리 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category ID.
                * \endenglish
                * @return   const wchar_t* categoryId
                */
                const wchar_t* GetCategoryId() const;

                /*!
                * \korean
                * @brief    카테고리 이름을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category name.
                * \endenglish
                * @return   const wchar_t* categoryName
                */
                const wchar_t* GetCategoryName() const;

                /*!
                * \korean
                * @brief    통화 코드를 가져옵니다.
                * @details  상품 가격 표시에 사용 합니다.
                * \endkorean
                * \english
                * @brief    Get the currency code.
                * @details  Used to display product prices.
                * \endenglish
                * @return   const wchar_t* currencyCode
                */
                const wchar_t* GetCurrencyCode() const;

                /*!
                * \korean
                * @brief    상품 정가(결제)를 가져옵니다.
                * @details  상품의 정가 가격 표시에만 사용하세요.
                * \endkorean
                * \english
                * @brief    Get the product price (payment).
                * @details  Use only for displaying the regular price of the product.
                * \endenglish
                * @return   double price
                */
                double GetPrice() const;

                /*!
                * \korean
                * @brief    상품 정가(전시)를 가져옵니다.
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Get the product price (display).
                * @details  Currently not in use
                * \endenglish
                * @return   double displayPrice
                */
                double GetDisplayPrice() const;

                /*!
                * \korean
                * @brief    상품 정가 문자열(전시)을 가져옵니다.
                * @details  정가 가격 표시에만 사용하세요.
                * \endkorean
                * \english
                * @brief    Get the product price string (display).
                * @details  Use only for displaying the regular price.
                * \endenglish
                * @return   const wchar_t* displayPriceString
                */
                const wchar_t* GetDisplayPriceString() const;

                /*!
                * \korean
                * @brief    상품 판매가(결제)를 가져옵니다.
                * @details  상점에 실제 판매가를 표시할때와 상품 구매 요청시 전달하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Get the product sale price (payment).
                * @details  Used when displaying the actual sale price in the store and when requesting product purchase.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * @return   double salePrice
                */
                double GetSalePrice() const;

                /*!
                * \korean
                * @brief    상품 판매가(전시)를 가져옵니다.
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Get the product sale price (display).
                * @details  Currently not in use
                * \endenglish
                * @return   double displaySalePrice
                */
                double GetDisplaySalePrice() const;

                /*!
                * \korean
                * @brief    상품 판매가 문자열(전시)을 가져옵니다.
                * @details  상점에 통화기호가 포함된 실제 판매가를 표시할때 사용하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Get the product sale price string (display).
                * @details  Used when displaying the actual sale price including the currency symbol in the store.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * \endenglish
                * @return   const wchar_t* displaySalePriceString
                */
                const wchar_t* GetDisplaySalePriceString() const;

                /*!
                * \korean
                * @brief    할인 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get if there is a discount.
                * \endenglish
                * @return   bool isDiscount
                */
                bool IsDiscount() const;

                /*!
                * \korean
                * @brief    할인 유형을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount type.
                * \endenglish
                * @return   DiscountType discountType
                */
                DiscountType GetDiscountType() const;

                /*!
                * \korean
                * @brief    할인 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount value.
                * \endenglish
                * @return   int32_t discountTypeValue
                */
                int32_t GetDiscountTypeValue() const;

                /*!
                * \korean
                * @brief    할인 시작 일자(epoch time milliseconds)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount start date (epoch time milliseconds).
                * \endenglish
                * @return   int64_t discountBeginDate
                */
                int64_t GetDiscountBeginDate() const;

                /*!
                * \korean
                * @brief    할인 종료 일자(epoch time milliseconds)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the discount end date (epoch time milliseconds).
                * \endenglish
                * @return   int64_t discountEndDate
                */
                int64_t GetDiscountEndDate() const;

                /*!
                * \korean
                * @brief    상품 총 판매수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the total quantity of product sales.
                * \endenglish
                * @return   int32_t totalQuantity
                */
                int32_t GetTotalQuantity() const;

                /*!
                * \korean
                * @brief    회원 구매 수량을 가져옵니다.
                * @details  로그인 한 계정 별 구매 수량입니다.
                * \endkorean
                * \english
                * @brief    Get the member purchase quantity.
                * @details  Purchase quantity per logged-in account.
                * \endenglish
                * @return   int32_t memberQuantity
                */
                int32_t GetMemberQuantity() const;

                /*!
                * \korean
                * @brief    guid 구매 수량을 가져옵니다.
                * @details  게임의 Unique 한 계정 별 구매 수량입니다.
                * \endkorean
                * \english
                * @brief    Get the guid purchase quantity.
                * @details  Purchase quantity per unique account in the game.
                * \endenglish
                * @return   int32_t guidQuantity
                */
                int32_t GetGuidQuantity() const;

                /*!
                * \korean
                * @brief    대표 상품 이미지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the representative product image.
                * \endenglish
                * @return   const wchar_t* thumbnailUrl
                */
                const wchar_t* GetThumbnailUrl() const;

                /*!
                * \korean
                * @brief    청약 철회 가능 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get if withdrawal is possible.
                * \endenglish
                * @return   bool canWithdraw
                */
                bool CanWithdraw() const;

                /*!
                * \korean
                * @brief    구매 여부 (구매 이력이 한 건 이상인 경우 true)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the purchase status (true if there is at least one purchase history).
                * \endenglish
                * @return   bool purchasedAtLeastOnce
                */
                bool GetPurchasedAtLeastOnce() const;

                /*!
                * \korean
                * @brief    구매 여부 (구매 이력이 한 건 이상인 경우 true)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the purchase status (true if there is at least one purchase history).
                * \endenglish
                * @return   PurchaseLimitTypeCode purchaseLimitTypeCode
                */
                PurchaseLimitTypeCode GetPurchaseLimitTypeCode() const;

                /*!
                * \korean
                * @brief    판매 제한 수량을 가져옵니다.
                * @details  GetPurchaseLimitTypeCode() 값이 PurchaseLimitTypeCode::CHARACTER 일 경우 회원 별 제한 수량
                * \endkorean
                * \english
                * @brief    Get the sale limit quantity.
                * @details  If the value of GetPurchaseLimitTypeCode() is PurchaseLimitTypeCode::CHARACTER, it is the limit quantity per member.
                * \endenglish
                * @return   int32_t purchaseLimitCount
                */
                int32_t GetPurchaseLimitCount() const;

                /*!
                * \korean
                * @brief    총 판매 제한 수량 (0일 경우 무제한)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the total sale limit quantity (0 for unlimited).
                * \endenglish
                * @return   int32_t saleLimitCount
                */
                int32_t GetSaleLimitCount() const;

                /*!
                * \korean
                * @brief    판매 시작 일자(epoch time milliseconds)를 가져옵니다.
                * @details  판매 기간이 상시 일 경우 null(SDK: 0) 리턴
                * \endkorean
                * \english
                * @brief    Get the sale start date (epoch time milliseconds).
                * @details  If the sale period is all day, return null (SDK: 0).
                * \endenglish
                * @return   int64_t saleBeginDate
                */
                int64_t GetSaleBeginDate() const;

                /*!
                * \korean
                * @brief    판매 종료 일자(epoch time milliseconds)를 가져옵니다.
                * @details  판매 기간이 상시 일 경우 null(SDK: 0) 리턴
                * \endkorean
                * \english
                * @brief    Get the sale end date (epoch time milliseconds).
                * @details  If the sale period is all day, return null (SDK: 0).
                * \endenglish
                * @return   int64_t saleEndDate
                */
                int64_t GetSaleEndDate() const;

                /*!
                * \korean
                * @brief    구매 가능 코드를 가져옵니다.
                            구매 가능 코드가 1이어도, 남은 수량 대비 더 많은 수량으로 구매 요청 시 구매 불가 응답이 올 수 있습니다.
                * @details  ( 1: 구매 가능, 2: 구매 불가(구매 제한 초과) )
                * \endkorean
                * \english
                * @brief    Get the purchase availability code.
                            Even if the purchase availability code is 1, a purchase unavailable response may come when requesting a purchase with a quantity greater than the remaining quantity.
                * @details  ( 1: Purchase available, 2: Purchase not available (purchase limit exceeded) )
                * \endenglish
                * @return   int64_t saleEndDate
                */
                int16_t GetPurchaseAvailabilityCode() const;

            public:
                StovePCProductEx();
                StovePCProductEx(const StovePCProductEx& rhs);
                StovePCProductEx(const StovePCProductExCpp* rhs);
                ~StovePCProductEx();

                StovePCProductEx& operator=(const StovePCProductEx& rhs);
                StovePCProductEx& operator=(const StovePCProductExCpp* rhs);

            private:
                void DeepCopy(const StovePCProductEx& rhs);
                void DeepCopy(const StovePCProductExCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    플랫폼 상품 아이디
                * \endkorean
                * \english
                * @brief    Platform product ID
                * \endenglish
                */
                int64_t productId;

                /*!
                * \korean
                * @brief    상품 아이디에 매핑되는 게임 내 아이템 아이디
                * \endkorean
                * \english
                * @brief    Game item ID mapped to the product ID
                * \endenglish
                */
                wchar_t* gameItemId = nullptr;

                /*!
                * \korean
                * @brief    상품명
                * \endkorean
                * \english
                * @brief    Product name
                * \endenglish
                */
                wchar_t* name = nullptr;

                /*!
                * \korean
                * @brief    상품 상세
                * \endkorean
                * \english
                * @brief    Product details
                * \endenglish
                */
                wchar_t* description = nullptr;

                /*!
                * \korean
                * @brief    개별 상품 수량
                * \endkorean
                * \english
                * @brief    Individual product quantity
                * \endenglish
                */
                int32_t quantity;

                /*!
                * \korean
                * @brief    아이템 유형 코드
                * \endkorean
                * \english
                * @brief    Item type code
                * \endenglish
                */
                ProductTypeCode productTypeCode;

                /*!
                * \korean
                * @brief    카테고리 아이디
                * \endkorean
                * \english
                * @brief    Category ID
                * \endenglish
                */
                wchar_t* categoryId = nullptr;

                /*!
                * \korean
                * @brief    카테고리 이름
                * \endkorean
                * \english
                * @brief    Category name
                * \endenglish
                */
                wchar_t* categoryName = nullptr;

                /*!
                * \korean
                * @brief    통화 코드
                * @details  상품 가격 표시에 사용
                * \endkorean
                * \english
                * @brief    Currency code
                * @details  Used to display product prices
                * \endenglish
                */
                wchar_t* currencyCode = nullptr;

                /*!
                * \korean
                * @brief    상품 정가(결제)
                * @details  상품의 정가 가격 표시에만 사용하세요
                * \endkorean
                * \english
                * @brief    Product price (payment)
                * @details  Use only for displaying the regular price of the product
                * \endenglish
                */
                double price;

                /*!
                * \korean
                * @brief    상품 정가(전시)
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Product price (display)
                * @details  Currently not in use
                * \endenglish
                */
                double displayPrice;

                /*!
                * \korean
                * @brief    상품 정가 문자열(전시)
                * @details  정가 가격 표시에만 사용하세요
                * \endkorean
                * \english
                * @brief    Product price string (display)
                * @details  Use only for displaying the regular price
                * \endenglish
                */
                wchar_t* displayPriceString = nullptr;

                /*!
                * \korean
                * @brief    상품 판매가(결제)
                * @details  상점에 실제 판매가를 표시할때와 상품 구매 요청시 전달하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Product sale price (payment)
                * @details  Used when displaying the actual sale price in the store and when requesting product purchase.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * \endenglish
                */
                double salePrice;

                /*!
                * \korean
                * @brief    상품 판매가(전시)
                * @details  현재 사용 되지 않음
                * \endkorean
                * \english
                * @brief    Product sale price (display)
                * @details  Currently not in use
                * \endenglish
                */
                double displaySalePrice;

                /*!
                * \korean
                * @brief    상품 판매가 문자열(전시)
                * @details  상점에 통화기호가 포함된 실제 판매가를 표시할때 사용하는 값 입니다.
                            파트너스에서 할인 설정하면 할인 가격이 자동 반영 됩니다.
                * \endkorean
                * \english
                * @brief    Product sale price string (display)
                * @details  Used when displaying the actual sale price including the currency symbol in the store.
                            If a discount is set by the partner, the discount price is automatically reflected.
                * \endenglish
                */
                wchar_t* displaySalePriceString = nullptr;

                /*!
                * \korean
                * @brief    할인 여부
                * \endkorean
                * \english
                * @brief    Discount availability
                * \endenglish
                */
                bool isDiscount;

                /*!
                * \korean
                * @brief    할인 유형
                * \endkorean
                * \english
                * @brief    Discount type
                * \endenglish
                */
                DiscountType discountType;

                /*!
                * \korean
                * @brief    할인 값
                * \endkorean
                * \english
                * @brief    Discount value
                * \endenglish
                */
                int32_t discountTypeValue;

                /*!
                * \korean
                * @brief    할인 시작 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Discount start date (epoch time milliseconds)
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t discountBeginDate;

                /*!
                * \korean
                * @brief    할인 종료 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Discount end date
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t discountEndDate;

                /*!
                * \korean
                * @brief    상품 총 판매수량
                * \endkorean
                * \english
                * @brief    Total quantity of product sales
                * \endenglish
                */
                int32_t totalQuantity;

                /*!
                * \korean
                * @brief    회원 구매 수량
                * \endkorean
                * \english
                * @brief    Member purchase quantity
                * \endenglish
                */
                int32_t memberQuantity;

                /*!
                * \korean
                * @brief    guid 구매 수량
                * @details  게임의 Unique 한 계정 별 구매 수량입니다.
                * \endkorean
                * \english
                * @brief    guid purchase quantity
                * @details  Purchase quantity per unique account in the game
                * \endenglish
                */
                int32_t guidQuantity;

                /*!
                * \korean
                * @brief    대표 상품 이미지
                * \endkorean
                * \english
                * @brief    Representative product image
                * \endenglish
                */
                wchar_t* thumbnailUrl = nullptr;

                /*!
                * \korean
                * @brief    청약 철회 가능 여부
                * \endkorean
                * \english
                * @brief    Check if withdrawal is possible
                * \endenglish
                */
                bool canWithdraw;

                /*!
                * \korean
                * @brief    구매 여부 (구매 이력이 한 건 이상인 경우 true)
                * \endkorean
                * \english
                * @brief    Check the purchase status (true if there is at least one purchase history)
                * \endenglish
                */
                bool purchasedAtLeastOnce;

                /*!
                * \korean
                * @brief    할인 유형
                * @details  1. 무제한 2. 회원별 3. 캐릭터별
                * \endkorean
                * \english
                * @brief    Discount type
                * @details  1. Unlimited 2. Per member 3. Per character
                * \endenglish
                */
                PurchaseLimitTypeCode purchaseLimitTypeCode;

                /*!
                * \korean
                * @brief    판매 제한 수량
                * @details  GetPurchaseLimitTypeCode() 값이 PurchaseLimitTypeCode::CHARACTER 일 경우 회원 별 제한 수량
                * \endkorean
                * \english
                * @brief    Sale limit quantity
                * @details  If the value of GetPurchaseLimitTypeCode() is PurchaseLimitTypeCode::CHARACTER, it is the limit quantity per member
                * \endenglish
                */
                int32_t purchaseLimitCount;

                /*!
                * \korean
                * @brief    총 판매 제한 수량
                * @details  0일 경우 무제한
                * \endkorean
                * \english
                * @brief    Total sale limit quantity
                * @details  0 for unlimited
                * \endenglish
                */
                int32_t saleLimitCount;

                /*!
                * \korean
                * @brief    판매 시작 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Sale start date
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t saleBeginDate = 0LL;

                /*!
                * \korean
                * @brief    판매 종료 일자
                * @details  epoch time milliseconds
                * \endkorean
                * \english
                * @brief    Sale end date
                * @details  epoch time milliseconds
                * \endenglish
                */
                int64_t saleEndDate = 0LL;

                /*!
                * \korean
                * @brief    구매 가능 코드
                * @details  ( 1: 구매 가능, 2: 구매 불가(구매 제한 초과) )
                * \endkorean
                * \english
                * @brief    Purchase availability code
                * @details  ( 1: Purchase available, 2: Purchase not available (purchase limit exceeded) )
                * \endenglish
                */
                int16_t purchaseAvailabilityCode = 0LL;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCOrderProduct
            * \korean
            * @brief 구매할 상품의 정보를 전달하는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that delivers information about the product to be purchased.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCOrderProduct
            {
            public:
                /*!
                * \korean
                * @brief    플랫폼 상품 ID를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the platform product ID.
                * \endenglish
                * @return   int64_t productId
                */
                int64_t GetProductId() const;

                /*!
                * \korean
                * @brief    플랫폼 상품 ID를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the platform product ID.
                * \endenglish
                * @param    int64_t productId
                */
                void SetProductId(int64_t id);

                /*!
                * \korean
                * @brief    상품 판매가를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product sale price.
                * \endenglish
                * @return   double salePrice
                */
                double GetSalePrice() const;

                /*!
                * \korean
                * @brief    상품 판매가를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the product sale price.
                * \endenglish
                * @param    double salePrice
                */
                void SetSalePrice(double salePrice);

                /*!
                * \korean
                * @brief    수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the quantity.
                * \endenglish
                * @return   int32_t quantity
                */
                int32_t GetQuantity() const;

                /*!
                * \korean
                * @brief    수량을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the quantity.
                * \endenglish
                * @param    int32_t quantity
                */
                void SetQuantity(int32_t quantity);

            public:
                StovePCOrderProduct();
                StovePCOrderProduct(const StovePCOrderProduct& rhs);
                StovePCOrderProduct(const StovePCOrderProductCpp* rhs);
                ~StovePCOrderProduct() = default;

                StovePCOrderProduct& operator=(const StovePCOrderProduct& rhs);
                StovePCOrderProduct& operator=(const StovePCOrderProductCpp* rhs);

            private:
                void DeepCopy(const StovePCOrderProduct& rhs);
                void DeepCopy(const StovePCOrderProductCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    플랫폼 상품 ID
                * \endkorean
                * \english
                * @brief    Platform product ID
                * \endenglish
                */
                int64_t productId;

                /*!
                * \korean
                * @brief    상품 판매가
                * \endkorean
                * \english
                * @brief    Product sale price
                * \endenglish
                */
                double salePrice;

                /*!
                * \korean
                * @brief    수량
                * \endkorean
                * \english
                * @brief    Quantity
                * \endenglish
                */
                int32_t quantity;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCPurchaseOption
            * \korean
            * @brief IAP_StartPurchase API에 대한 옵션을 전달하는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that delivers options for the IAP_StartPurchase API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCPurchaseOption
            {
            public:
                /*!
                * \korean
                * @brief    IAPSDK_StartPurchase 메소드 수행 시 동작 방식을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the operation when the IAPSDK_StartPurchase method is executed.
                * \endenglish
                * @return   StovePCPurchaseOperation operation
                */
                StovePCPurchaseOperation GetOperation() const;

                /*!
                * \korean
                * @brief    IAPSDK_StartPurchase 메소드 수행 시 동작 방식을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the operation when the IAPSDK_StartPurchase method is executed.
                * @param    StovePCPurchaseOperation operation
                */
                void SetOperation(StovePCPurchaseOperation operation);

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 (operation != DEFAULT일 때 적용) 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the type when using the Stove Webview (applied when operation != DEFAULT).
                * \endenglish
                * @return   Base::WebViewMode webviewMode
                */
                Base::WebViewMode GetWebviewMode() const;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 (operation != DEFAULT일 때 적용) 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the type when using the Stove Webview (applied when operation != DEFAULT).
                * \endenglish
                * @param    Base::WebViewMode webviewMode
                */
                void SetWebviewMode(Base::WebViewMode mode);

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 위치를 (operation != DEFAULT일 때 적용) 가져옵니다.
                * @param    __out int32_t* x Webview의 x축 위치
                * @param    __out int32_t* y Webview의 y축 위치
                * @param    __out int32_t* width Webview의 가로 길이
                * @param    __out int32_t* height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Get the position of the Webview for displaying the Stove payment page (applied when operation != DEFAULT).
                * @param    __out int32_t* x x-axis position of the Webview
                * @param    __out int32_t* y y-axis position of the Webview
                * @param    __out int32_t* width width of the Webview
                * @param    __out int32_t* height height of the Webview
                * \endenglish
                */
                void GetWebviewRect(__out int32_t* x, __out int32_t* y, __out int32_t* width, __out int32_t* height) const;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 위치를 (operation != DEFAULT일 때 적용) 설정합니다.
                * @param    int32_t x Webview의 x축 위치
                * @param    int32_t y Webview의 y축 위치
                * @param    int32_t width Webview의 가로 길이
                * @param    int32_t height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Set the position of the Webview for displaying the Stove payment page (applied when operation != DEFAULT).
                * @param    int32_t x x-axis position of the Webview
                * @param    int32_t y y-axis position of the Webview
                * @param    int32_t width width of the Webview
                * @param    int32_t height height of the Webview
                * \endenglish
                */
                void SetWebviewRect(int32_t x, int32_t y, int32_t width, int32_t height);

            public:
                StovePCPurchaseOption();
                StovePCPurchaseOption(const StovePCPurchaseOption& rhs);
                StovePCPurchaseOption(const StovePCPurchaseOptionCpp* rhs);
                ~StovePCPurchaseOption() = default;

                StovePCPurchaseOption& operator=(const StovePCPurchaseOption& rhs);
                StovePCPurchaseOption& operator=(const StovePCPurchaseOptionCpp* rhs);

            private:
                void DeepCopy(const StovePCPurchaseOption& rhs);
                void DeepCopy(const StovePCPurchaseOptionCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    IAPSDK_StartPurchase 메소드 수행 시 동작 방식
                * \endkorean
                * \english
                * @brief    Operation when the IAPSDK_StartPurchase method is executed
                * \endenglish
                */
                StovePCPurchaseOperation operation;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 결정
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    Determine the type when using the Stove Webview
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                Base::WebViewMode webviewMode;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 x축 위치
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    x-axis position of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewPosX;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 y축 위치
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    y-axis position of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewPosY;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 가로 길이
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    Width of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewWidth;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 세로 길이
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    Height of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewHeight;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCStartPurchaseParam
            * \korean
            * @brief IAP_StartPurchase API 실행 시 전달할 값을 담는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that contains the values to be passed when executing the IAP_StartPurchase API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCStartPurchaseParam
            {
            public:
                /*!
                * \korean
                * @brief    구매할 상품 정보 목록을 배열로 생성합니다.
                * @return   uint32_t count 배열의 개수
                * \endkorean
                * \english
                * @brief    Create an array of product information to be purchased.
                * @return   uint32_t count Number of arrays
                * \endenglish
                */
                void CreateOrderProduct(uint32_t count);

                /*!
                * \korean
                * @brief    구매할 상품 정보 목록의 값을 가져옵니다.
                * @param    uint32_t index 배열의 index
                * @return   const StovePCOrderProduct* product 상품 정보
                * \endkorean
                * \english
                * @brief    Get the value of the product information list to be purchased.
                * @param    uint32_t index index of the array
                * @return   const StovePCOrderProduct* product product information
                * \endenglish
                */
                const StovePCOrderProduct* GetOrderProduct(int32_t index) const;

                /*!
                * \korean
                * @brief    구매할 상품 정보 목록의 값을 설정합니다.
                * @param    uint32_t index 배열의 index
                * @param    const StovePCOrderProduct* product 상품 정보
                * \endkorean
                * \english
                * @brief    Set the value of the product information list to be purchased.
                * @param    uint32_t index index of the array
                * @param    const StovePCOrderProduct* product product information
                * \endenglish
                */
                void SetOrderProduct(int32_t index, const StovePCOrderProduct* product);

                /*!
                * \korean
                * @brief    구매할 상품 정보 목록의 개수를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the number of product information lists to be purchased.
                * \endenglish
                * @return   uint32_t productsCount
                */
                uint32_t GetOrderProductCount() const;

                /*!
                * \korean
                * @brief    API 실행 옵션을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the API execution option.
                * \endenglish
                * @return   StovePCPurchaseOption option
                */
                StovePCPurchaseOption GetPurchaseOption() const;

                /*!
                * \korean
                * @brief    API 실행 옵션을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the API execution option.
                * \endenglish
                * @param    StovePCPurchaseOption option
                */
                void SetPurchaseOption(StovePCPurchaseOption option);

                /*!
                * \korean
                * @brief    서비스 주문 번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the service order number.
                * \endenglish
                * @return   const wchar_t* serviceTxnNo
                */
                const wchar_t* GetServiceTxnNo() const;

                /*!
                * \korean
                * @brief    서비스 주문 번호를 설정합니다.
                * @details  필수가 아니며 필요에 따라 설정합니다. 최대 길이는 50자입니다. 특수문자는 포함되면 안됩니다.
                *           게임에서 발급 한 주문 번호
                *           NOTI 서버를 통해 전달
                * \endkorean
                * \english
                * @brief    Set the service order number.
                * @details  It is not mandatory and can be set as needed. The maximum length is 50 characters. Special characters should not be included.
                *           Order number issued by the game
                *           Delivered through the NOTI server
                * @param    const wchar_t* serviceTxnNo
                */
                void SetServiceTxnNo(const wchar_t* serviceTxnNo);

                /*!
                * \korean
                * @brief    요청 추가 데이터를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the request additional data.
                * \endenglish
                * @return   const wchar_t* extraData
                */
                const wchar_t* GetExtraData() const;

                /*!
                * \korean
                * @brief    요청 추가 데이터를 설정합니다.
                * @details  필수가 아니며 필요에 따라 설정합니다. JSON 형식의 문자열이어야 합니다. 최대 길이는 500자입니다.
                *           게임에서 전달 받고자 하는 추가 정보
                *           NOTI 서버를 통해 전달
                * \endkorean
                * \english
                * @brief    Set the request additional data.
                * @details  It is not mandatory and can be set as needed. It must be a string in JSON format. The maximum length is 500 characters.
                *           Additional information to be received from the game
                *           Delivered through the NOTI server
                * \endenglish
                * @param    const wchar_t* extraData
                */
                void SetExtraData(const wchar_t* extraData);

            public:
                StovePCStartPurchaseParam();
                StovePCStartPurchaseParam(const StovePCStartPurchaseParam& rhs);
                StovePCStartPurchaseParam(const StovePCStartPurchaseParamCpp* rhs);
                ~StovePCStartPurchaseParam();

                StovePCStartPurchaseParam& operator=(const StovePCStartPurchaseParam& rhs);
                StovePCStartPurchaseParam& operator=(const StovePCStartPurchaseParamCpp* rhs);

            private:
                void DeepCopy(const StovePCStartPurchaseParam& rhs);
                void DeepCopy(const StovePCStartPurchaseParamCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    구매할 상품 정보 목록
                * \endkorean
                * \english
                * @brief    List of product information to be purchased
                * \endenglish
                */
                StovePCOrderProduct* products;

                /*!
                * \korean
                * @brief    구매할 상품 정보 목록의 개수
                * \endkorean
                * \english
                * @brief    Number of product information lists to be purchased
                * \endenglish
                */
                uint32_t productsCount;

                /*!
                * \korean
                * @brief    API 실행 옵션
                * \endkorean
                * \english
                * @brief    API execution option
                * \endenglish
                */
                StovePCPurchaseOption option;

                /*!
                * \korean
                * @brief    서비스 주문 번호
                * @details  필수가 아니며 필요에 따라 설정합니다. 최대 길이는 50자입니다. 특수문자는 포함되면 안됩니다.
                *           게임에서 발급 한 주문 번호
                *           NOTI 서버를 통해 전달
                * \endkorean
                * \english
                * @brief    Service order number
                * @details  It is not mandatory and can be set as needed. It must be a string in JSON format. The maximum length is 500 characters.
                *           Additional information to be received from the game
                *           Delivered through the NOTI server
                * \endenglish
                */
                wchar_t* serviceTxnNo = nullptr;

                /*!
                * \korean
                * @brief    요청 추가 데이터
                * @details  필수가 아니며 필요에 따라 설정합니다. JSON 형식의 문자열이어야 합니다. 최대 길이는 500자입니다.
                *           게임에서 전달 받고자 하는 추가 정보
                *           NOTI 서버를 통해 전달
                * \endkorean
                * \english
                * @brief    Request additional data
                * @details  It is not mandatory and can be set as needed. It must be a string in JSON format. The maximum length is 500 characters.
                *           Additional information to be received from the game
                *           Delivered through the NOTI server
                * \endenglish
                */
                wchar_t* extraData = nullptr;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCPurchasedProduct
            * \korean
            * @brief 구매한 상품의 정보를 전달하는 구조체입니다. IAP_StartPurchase 및 IAP_ConfirmPurchase 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief A structure that delivers information about the purchased product. Used when delivering results to the IAP_StartPurchase and IAP_ConfirmPurchase callbacks.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCPurchasedProduct
            {
            public:
                /*!
                * \korean
                * @brief    구매 상세 번호 목록 (구매 상품 TID)를 가져옵니다.
                * @details  구매 요청 API 에서 응답 받은 거래 고유 마스터 번호(결제 TID)
                * \endkorean
                * \english
                * @brief    Get the transaction detail number list (purchase product TID).
                * @details  Unique transaction master number received in the purchase request API (payment TID)
                * \endenglish
                * @return   int64_t productId
                */
                int64_t GetTransactionDetailNumber() const;

                /*!
                * \korean
                * @brief    구매 상세 번호 목록 (구매 상품 TID)를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the transaction detail number list (purchase product TID).
                * \endenglish
                * @param    int64_t productId
                */
                void SetTransactionDetailNumber(int64_t transactionDetailNumber);

                /*!
                * \korean
                * @brief    플랫폼 상품 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the platform product ID.
                * \endenglish
                * @return   int64_t productId
                */
                int64_t GetProductId() const;

                /*!
                * \korean
                * @brief    플랫폼 상품 아이디를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the platform product ID.
                * \endenglish
                * @param    int64_t productId
                */
                void SetProductId(int64_t productId);

                /*!
                * \korean
                * @brief    카테고리 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the category ID.
                * \endenglish
                * @return   const wchar_t* categoryId
                */
                const wchar_t* GetCategoryId() const;

                /*!
                * \korean
                * @brief    카테고리 아이디를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the category ID.
                * \endenglish
                * @param    const wchar_t* categoryId
                */
                void SetCategoryId(const wchar_t* categoryId);

                /*!
                * \korean
                * @brief    상품 총 판매수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the total quantity of product sales.
                * \endenglish
                * @return   int32_t totalQuantity
                */
                int32_t GetTotalQuantity() const;

                /*!
                * \korean
                * @brief    상품 총 판매수량을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the total quantity of product sales.
                * \endenglish
                * @param    int32_t totalQuantity
                */
                void SetTotalQuantity(int32_t totalQuantity);

                /*!
                * \korean
                * @brief    회원 구매 수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the member purchase quantity.
                * \endenglish
                * @return   int32_t memberQuantity
                */
                int32_t GetMemberQuantity() const;

                /*!
                * \korean
                * @brief    회원 구매 수량을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the member purchase quantity.
                * \endenglish
                * @param    int32_t memberQuantity
                */
                void SetMemberQuantity(int32_t memberQuantity);

                /*!
                * \korean
                * @brief    guid 구매 수량을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the guid purchase quantity.
                * \endenglish
                * @return   int32_t guidQuantity
                */
                int32_t GetGuidQuantity() const;

                /*!
                * \korean
                * @brief    guid 구매 수량을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the guid purchase quantity.
                * \endenglish
                * @param    int32_t guidQuantity
                */
                void SetGuidQuantity(int32_t guidQuantity);

            public:
                StovePCPurchasedProduct();
                StovePCPurchasedProduct(const StovePCPurchasedProduct& rhs);
                StovePCPurchasedProduct(const StovePCPurchasedProductCpp* rhs);
                ~StovePCPurchasedProduct();

                StovePCPurchasedProduct& operator=(const StovePCPurchasedProduct& rhs);
                StovePCPurchasedProduct& operator=(const StovePCPurchasedProductCpp* rhs);

            private:
                void DeepCopy(const StovePCPurchasedProduct& rhs);
                void DeepCopy(const StovePCPurchasedProductCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    구매 상세 번호 목록 (구매 상품 TID)
                * @details  구매 요청 API 에서 응답 받은 거래 고유 마스터 번호(결제 TID)
                * \endkorean
                * \english
                * @brief    Transaction detail number list (purchase product TID)
                * @details  Unique transaction master number received in the purchase request API (payment TID)
                * \endenglish
                */
                int64_t transactionDetailNumber;

                /*!
                * \korean
                * @brief    플랫폼 상품 아이디
                * \endkorean
                * \english
                * @brief    Platform product ID
                * \endenglish
                */
                int64_t productId;

                /*!
                * \korean
                * @brief    카테고리 아이디
                * \endkorean
                * \english
                * @brief    Category ID
                * \endenglish
                */
                wchar_t* categoryId = nullptr;

                /*!
                * \korean
                * @brief    상품 총 판매수량
                * \endkorean
                * \english
                * @brief    Total quantity of product sales
                * \endenglish
                */
                int32_t totalQuantity;

                /*!
                * \korean
                * @brief    회원 구매 수량
                * \endkorean
                * \english
                * @brief    Member purchase quantity
                * \endenglish
                */
                int32_t memberQuantity;

                /*!
                * \korean
                * @brief    guid 구매 수량
                * \endkorean
                * \english
                * @brief    guid purchase quantity
                * \endenglish
                */
                int32_t guidQuantity;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCChargeInfo
            * \korean
            * @brief 상품을 구매할 때 사용한 재화 정보를 전달하는 구조체입니다. IAP_StartPurchase 및 IAP_ConfirmPurchaseCpp 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief A structure that delivers information about the currency used when purchasing a product. Used when delivering results to the IAP_StartPurchase and IAP_ConfirmPurchaseCpp callbacks.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCChargeInfo
            {
            public:
                /*!
                * \korean
                * @brief    결제 가격을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the payment price.
                * \endenglish
                * @return   double chargeDeductVal
                */
                double GetChargeDeductVal() const;

                /*!
                * \korean
                * @brief    결제 가격을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the payment price.
                * \endenglish
                * @param    double chargeDeductVal
                */
                void SetChargeDeductVal(double chargeDeductVal);

                /*!
                * \korean
                * @brief    결제 가격에 대한 캐시 전환 가격을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the cash conversion price for the payment price.
                * \endenglish
                * @return   double chargeDisplayDeductVal
                */
                double GetChargeDisplayDeductVal() const;

                /*!
                * \korean
                * @brief    결제 가격에 대한 캐시 전환 가격을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the cash conversion price for the payment price.
                * \endenglish
                * @param    double chargeDisplayDeductVal
                */
                void SetChargeDisplayDeductVal(double chargeDisplayDeductVal);

                /*!
                * \korean
                * @brief    결제 수단 코드를 가져옵니다.
                * @details  98은 STOVE 캐시, 99는 포인트, 그 외의 값은 PG 결제 수단을 의미합니다.
                * \endkorean
                * \english
                * @brief    Get the payment method code.
                * @details  98 is STOVE cash, 99 is points, and other values represent PG payment methods.
                * \endenglish
                * @return   int32_t chargeType
                */
                int32_t GetChargeType() const;

                /*!
                * \korean
                * @brief    결제 수단 코드를 설정합니다.
                * @details  98은 STOVE 캐시, 99는 포인트, 그 외의 값은 PG 결제 수단을 의미합니다.
                * \endkorean
                * \english
                * @brief    Set the payment method code.
                * @details  98 is STOVE cash, 99 is points, and other values represent PG payment methods.
                * \endenglish
                * @param    int32_t chargeType
                */
                void SetChargeType(int32_t chargeType);

                /*!
                * \korean
                * @brief    결제 수단 이름를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the payment method name.
                * \endenglish
                * @return   const wchar_t* chargeTypeName
                */
                const wchar_t* GetChargeTypeName() const;

                /*!
                * \koeran
                * @brief    결제 수단 이름를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the payment method name.
                * \endenglish
                * @param   const wchar_t* chargeTypeName
                */
                void SetChargeTypeName(const wchar_t* chargeTypeName);

            public:
                StovePCChargeInfo();
                StovePCChargeInfo(const StovePCChargeInfo& rhs);
                StovePCChargeInfo(const StovePCChargeInfoCpp* rhs);
                ~StovePCChargeInfo();

                StovePCChargeInfo& operator=(const StovePCChargeInfo& rhs);
                StovePCChargeInfo& operator=(const StovePCChargeInfoCpp* rhs);

            private:
                void DeepCopy(const StovePCChargeInfo& rhs);
                void DeepCopy(const StovePCChargeInfoCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    결제 가격
                * \endkorean
                * \english
                * @brief    Payment price
                * \endenglish
                */
                double chargeDeductVal;

                /*!
                * \korean
                * @brief    결제 가격에 대한 캐시 전환 가격
                * \endkorean
                * \english
                * @brief    Cash conversion price for the payment price
                * \endenglish
                */
                double chargeDisplayDeductVal;

                /*!
                * \korean
                * @brief    결제 수단 코드
                * @details  98: STOVE 캐시, 99: 포인트, 그 외: PG 결제 수단
                * \endkorean
                * \english
                * @brief    Payment method code
                * @details  98: STOVE cash, 99: points, other: PG payment method
                * \endenglish
                */
                int32_t chargeType;

                /*!
                * \korean
                * @brief    결제 수단 이름
                * \endkorean
                * \english
                * @brief    Payment method name
                * \endenglish
                */
                wchar_t* chargeTypeName;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCPurchaseResult
            * \korean
            * @brief 구매 작업 결과 정보를 전달하는 구조체입니다. IAP_StartPurchase 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief A structure that delivers information about the purchase operation result. Used when delivering results to the IAP_StartPurchase callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCPurchaseResult
            {
            public:
                /*!
                * \korean
                * @brief    거래 고유 마스터 번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the unique transaction master number.
                * \endenglish
                * @return   int64_t transactionMasterNumber
                */
                int64_t GetTransactionMasterNumber() const;

                /*!
                * \korean
                * @brief    TransactionDetailNumbers(int64_t)를 배열로 생성합니다.
                * @param    uint32_t count 배열의 개수
                * \endkorean
                * \english
                * @brief    Create TransactionDetailNumbers(int64_t) as an array.
                * @param    uint32_t uint32_t count Number of arrays
                * \endenglish
                */
                const void CreateTransactionDetailNumberList(uint32_t count);

                /*!
                * \korean
                * @brief    TransactionDetailNumber(int64_t)의 값을 설정합니다.
                * @param    uint32_t index 배열의 index
                * @param    const int64_t transactionDetailNumber 설정할 값
                * \endkorean
                * \english
                * @brief    Set the value of TransactionDetailNumber(int64_t).
                * @param    uint32_t index index of the array
                * @param    const int64_t transactionDetailNumber value to set
                * \endenglish
                */
                void SetTransactionDetailNumber(uint32_t index, const int64_t transactionDetailNumber);

                /*!
                * \korean
                * @brief    구매 상세 번호 목록을 가져옵니다. (구매 상품 TID)
                * @param    uint32_t index 배열의 index
                * \endkorean
                * \english
                * @brief    Get the transaction detail number list (purchase product TID).
                * @param    uint32_t index index of the array
                * \endenglish
                * @return   int64_t transactionDetailNumbers
                */
                int64_t GetTransactionDetailNumbers(uint32_t index) const;

                /*!
                * \korean
                * @brief    TransactionDetailNumber(int64_t) 배열의 개수를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the number of TransactionDetailNumber(int64_t) arrays.
                * \endenglish
                * @return   uint32_t transactionDetailNumberCount
                */
                uint32_t GetTransactionDetailNumberCount() const;

                /*!
                * \korean
                * @brief    일회용 결제 URL을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the one-time payment URL.
                * \endenglish
                * @return   const wchar_t* oneTimePaymentUrl
                */
                const wchar_t* GetOneTimePaymentUrl() const;

                /*!
                * \korean
                * @brief    구매 진행 상태를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the purchase progress.
                * \endenglish
                * @return   PurchaseProgress purchaseProgress
                */
                PurchaseProgress GetPurchaseProgress() const;

                /*!
                * \korean
                * @brief    IAP_StartPurchase 호출 시 전송한 응답 추가 데이터를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the additional data sent when the IAP_StartPurchase is called.
                * \endenglish
                * @return   const wchar_t* extraData
                */
                const wchar_t* GetExtraData() const;

                /*!
                * \korean
                * @brief    구매 결과를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the purchase result.
                * \endenglish
                * @return   bool purchased
                */
                bool IsPurchased() const;

                /*!
                * \korean
                * @brief    StovePCPurchasedProduct를 배열로 생성합니다.
                * \endkorean
                * \english
                * @brief    Create StovePCPurchasedProduct as an array.
                * \endenglish
                * @param    uint32_t count 배열의 개수
                */
                void CreatePurchasedProductList(uint32_t count);

                /*!
                * \korean
                * @brief    StovePCPurchasedProduct의 값을 설정합니다.
                * @param    uint32_t index 배열의 index
                * @param    const StovePCPurchasedProduct* 설정할 값
                * \endkorean
                * \english
                * @brief    Set the value of StovePCPurchasedProduct.
                * @param    uint32_t index index of the array
                * @param    const StovePCPurchasedProduct* value to set
                * \endenglish
                */
                void SetPurchasedProduct(uint32_t index, const StovePCPurchasedProduct* purchasedProduct);

                /*!
                * \korean
                * @brief    StovePCPurchasedProduct의 값을 가져옵니다.
                * @param    uint32_t index 배열의 index
                * \endkorean
                * \english
                * @brief    Get the value of StovePCPurchasedProduct.
                * @param    uint32_t index index of the array
                * \endenglish
                * @return   const StovePCPurchasedProduct* purchasedProducts
                */
                const StovePCPurchasedProduct* GetPurchasedProduct(uint32_t index) const;

                /*!
                * \korean
                * @brief    StovePCPurchasedProduct 배열의 개수를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the number of StovePCPurchasedProduct arrays.
                * \endenglish
                * @return   uint32_t purchasedProductCount
                */
                uint32_t GetPurchasedProductCount() const;

                /*!
                * \korean
                * @brief    StovePCChargeInfo를 배열로 생성합니다.
                * @param    uint32_t count 배열의 개수
                * \endkorean
                * \english
                * @brief    Create StovePCChargeInfo as an array.
                * @param    uint32_t count Number of arrays
                * \endenglish
                */
                void CreateChargeInfoList(uint32_t count);

                /*!
                * \korean
                * @brief    StovePCChargeInfo의 값을 설정합니다.
                * @param    uint32_t index 배열의 index
                * @param    const StovePCChargeInfo* 설정할 값
                * \endkorean
                * \english
                * @brief    Set the value of StovePCChargeInfo.
                * @param    uint32_t index index of the array
                * @param    const StovePCChargeInfo* value to set
                * \endenglish
                */
                void SetChargeInfo(uint32_t index, const StovePCChargeInfo* chargeInfo);

                /*!
                * \korean
                * @brief    StovePCChargeInfo의 값을 가져옵니다.
                * @param    uint32_t index 배열의 index
                * \endkorean
                * \english
                * @brief    Get the value of StovePCChargeInfo.
                * @param    uint32_t index index of the array
                * \endenglish
                * @return   const StovePCChargeInfo* chargeInfos
                */
                const StovePCChargeInfo* GetChargeInfo(uint32_t index) const;

                /*!
                * \korean
                * @brief    StovePCChargeInfo 배열의 개수를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the number of StovePCChargeInfo arrays.
                * \endenglish
                * @return   uint32_t chargeInfoCount
                */
                uint32_t GetChargeInfoCount() const;

            public:
                StovePCPurchaseResult();
                StovePCPurchaseResult(const StovePCPurchaseResult& rhs);
                StovePCPurchaseResult(const StovePCPurchaseResultCpp* rhs);
                ~StovePCPurchaseResult();

                StovePCPurchaseResult& operator=(const StovePCPurchaseResult& rhs);
                StovePCPurchaseResult& operator=(const StovePCPurchaseResultCpp* rhs);

            private:
                void DeepCopy(const StovePCPurchaseResult& rhs);
                void DeepCopy(const StovePCPurchaseResultCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    거래 고유 마스터 번호 (결제 TID)
                * \endkorean
                * \english
                * @brief    Unique transaction master number (payment TID)
                * \endenglish
                */
                int64_t transactionMasterNumber;

                /*!
                * \korean
                * @brief    구매 상세 번호 목록 (구매 상품 TID)
                * \endkorean
                * \english
                * @brief    Transaction detail number list (purchase product TID)
                * \endenglish
                */
                int64_t* transactionDetailNumbers;

                /*!
                * \korean
                * @brief    구매 상세 번호 목록의 개수
                * \endkorean
                * \english
                * @brief    Number of transaction detail number lists
                * \endenglish
                */
                uint32_t transactionDetailNumberCount;

                /*!
                * \korean
                * @brief    일회용 결제 URL
                * \endkorean
                * \english
                * @brief    One-time payment URL
                * \endenglish
                */
                wchar_t* oneTimePaymentUrl = nullptr;

                /*!
                * \korean
                * @brief    구매 진행 상태
                * \endkorean
                * \english
                * @brief    Purchase progress
                * \endenglish
                */
                PurchaseProgress purchaseProgress;

                /*!
                * \korean
                * @brief    구매 결과
                * @details  StovePCPurchaseOperation == WITH_WEBVIEW_AND_CONFIRM_RESULT이고 결제 성공 시 true, 이외 경우에 false
                * \endkorean
                * \english
                * @brief    Purchase result
                * @details  true if StovePCPurchaseOperation == WITH_WEBVIEW_AND_CONFIRM_RESULT and payment is successful, false otherwise
                * \endenglish
                */
                bool purchased;

                /*!
                * \korean
                * @brief    IAP_StartPurchase 호출 시 전송한 응답 추가 데이터
                * \endkorean
                * \english
                * @brief    Additional data sent when the IAP_StartPurchase is called
                * \endenglish
                */
                wchar_t* extraData = nullptr;

                /*!
                * \korean
                * @brief    구매한 상품 목록
                * @details  StovePCPurchaseOperation == WITH_WEBVIEW_AND_CONFIRM_RESULT이고 결제 성공 시 제공
                * \endkorean
                * \english
                * @brief    List of purchased products
                * @details  Provided if StovePCPurchaseOperation == WITH_WEBVIEW_AND_CONFIRM_RESULT and payment is successful
                * \endenglish
                */
                StovePCPurchasedProduct* purchasedProducts;

                /*!
                * \korean
                * @brief    구매한 상품 목록의 개수
                * \endkorean
                * \english
                * @brief    Number of purchased product lists
                * \endenglish
                */
                uint32_t purchasedProductCount;

                /*!
                * \korean
                * @brief    구매 시 사용한 재화 정보 목록
                * \endkorean
                * \english
                * @brief    List of currency information used for purchase
                * \endenglish
                */
                StovePCChargeInfo* chargeInfos;

                /*!
                * \korean
                * @brief    구매 시 사용한 재화 정보 목록의 개수
                * \endkorean
                * \english
                * @brief    Number of currency information lists used for purchase
                * \endenglish
                */
                uint32_t chargeInfoCount;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCInventoryItem
            * \korean
            * @brief 구매 기록 정보를 전달하는 구조체입니다. IAP_FetchInventory 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief A structure that delivers purchase history information. Used when delivering results to the IAP_FetchInventory callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCInventoryItem
            {
            public:
                /*!
                * \koeran
                * @brief    거래 고유 마스터 번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the unique transaction master number.
                * \endenglish
                * @return   int64_t transactionMasterNumber
                */
                int64_t GetTransactionMasterNumber() const;

                /*!
                * \koeran
                * @brief    거래 고유 상세 번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the unique transaction detail number.
                * \endenglish
                * @return   int64_t transactionDetailNumber
                */
                int64_t GetTransactionDetailNumber() const;

                /*!
                * \koeran
                * @brief    플랫폼 상품 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the platform product ID.
                * \endenglish
                * @return   int64_t productId
                */
                int64_t GetProductId() const;

                /*!
                * \koeran
                * @brief    상품 아이디에 매핑되는 게임 내 아이템 아이디를 가져옵니다.
                * \endkoeran
                * \english
                * @brief    Get the game item ID mapped to the product ID.
                * \endenglish
                * @return   const wchar_t* gameItemId
                */
                const wchar_t* GetGameItemId() const;

                /*!
                * \koeran
                * @brief    상품명을 가져옵니다.
                * \endkoeran
                * \english
                * @brief    Get the product name.
                * \endenglish
                * @return   const wchar_t* productName
                */
                const wchar_t* GetProductName() const;

                /*!
                * \koeran
                * @brief    수량을 가져옵니다.
                * @details  구매 요청 시 전달 된 수량입니다.
                * \endkoeran
                * \english
                * @brief    Get the quantity.
                * @details  The quantity delivered when the purchase request is made.
                * \endenglish
                * @return   int32_t quantity
                */
                int32_t GetQuantity() const;

                /*!
                * \koeran
                * @brief    대표 상품 이미지를 가져옵니다.
                * \endkoeran
                * \english
                * @brief    Get the representative product image.
                * \endenglish
                * @return   const wchar_t* thumbnailUrl
                */
                const wchar_t* GetThumbnailUrl() const;

            public:
                StovePCInventoryItem();
                StovePCInventoryItem(const StovePCInventoryItem& rhs);
                StovePCInventoryItem(const StovePCInventoryItemCpp* rhs);
                ~StovePCInventoryItem();

                StovePCInventoryItem& operator=(const StovePCInventoryItem& rhs);
                StovePCInventoryItem& operator=(const StovePCInventoryItemCpp* rhs);

            private:
                void DeepCopy(const StovePCInventoryItem& rhs);
                void DeepCopy(const StovePCInventoryItemCpp* rhs);

            private:
                /*!
                * \koeran
                * @brief    거래 고유 마스터 번호
                * \endkoeran
                * \english
                * @brief    Unique transaction master number
                * \endenglish
                */
                int64_t transactionMasterNumber;

                /*!
                * \koeran
                * @brief    거래 고유 상세 번호
                * \endkoeran
                * \english
                * @brief    Unique transaction detail number
                * \endenglish
                */
                int64_t transactionDetailNumber;

                /*!
                * \koeran
                * @brief    플랫폼 상품 아이디
                * \endkoeran
                * \english
                * @brief    Platform product ID
                * \endenglish
                */
                int64_t productId;

                /*!
                * \koeran
                * @brief    상품 아이디에 매핑되는 게임 내 아이템 아이디
                * \endkoeran
                * \english
                * @brief    Game item ID mapped to the product ID
                * \endenglish
                */
                wchar_t* gameItemId = nullptr;

                /*!
                * \koeran
                * @brief    상품명
                * \endkoeran
                * \english
                * @brief    Product name
                * \endenglish
                */
                wchar_t* productName = nullptr;

                /*!
                * \koeran
                * @brief    수량
                * \endkoeran
                * \english
                * @brief    Quantity
                * \endenglish
                */
                int32_t quantity;

                /*!
                * \koeran
                * @brief    대표 상품 이미지
                * \endkoeran
                * \english
                * @brief    Representative product image
                * \endenglish
                */
                wchar_t* thumbnailUrl = nullptr;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCTermsOption
            * \korean
            * @brief IAP_FetchTermsAgreement API에 대한 옵션을 전달하는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that delivers options for the IAP_FetchTermsAgreement API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCTermsOption
            {
            public:
                /*!
                * \korean
                * @brief    IAP_FetchTermsAgreement 메소드 수행 시 동작 방식을 가져옵니다.
                * @return   StovePCTermsOperation operation
                * \endkorean
                * \english
                * @brief    Get the operation method when the IAP_FetchTermsAgreement method is executed.
                * @return   StovePCTermsOperation operation
                */
                StovePCTermsOperation GetOperation() const;

                /*!
                * \korean
                * @brief    IAP_FetchTermsAgreement 메소드 수행 시 동작 방식을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the operation method when the IAP_FetchTermsAgreement method is executed.
                * \endenglish
                * @param    StovePCTermsOperation operation
                */
                void SetOperation(StovePCTermsOperation operation);

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 (operation != DEFAULT일 때 적용) 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the type when using the Stove Webview (applied when operation != DEFAULT).
                * \endenglish
                * @return   Base::WebViewMode webviewMode
                */
                Base::WebViewMode GetWebviewMode() const;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 (operation != DEFAULT일 때 적용) 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the type when using the Stove Webview (applied when operation != DEFAULT).
                * \endenglish
                * @param    Base::WebViewMode webviewMode
                */
                void SetWebviewMode(Base::WebViewMode mode);

                /*!
                * \korean
                * @brief    Stove 약관 동의 페이지 표시용 Webview의 위치를 (operation != DEFAULT일 때 적용) 가져옵니다.
                * @param    __out int32_t* x Webview의 x축 위치
                * @param    __out int32_t* y Webview의 y축 위치
                * @param    __out int32_t* width Webview의 가로 길이
                * @param    __out int32_t* height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Get the position of the Webview for displaying the Stove terms agreement page (applied when operation != DEFAULT).
                * @param    __out int32_t* x x-axis position of the Webview
                * @param    __out int32_t* y y-axis position of the Webview
                * @param    __out int32_t* width width of the Webview
                * @param    __out int32_t* height height of the Webview
                * \endenglish
                */
                void GetWebviewRect(__out int32_t* x, __out int32_t* y, __out int32_t* width, __out int32_t* height) const;

                /*!
                * \korean
                * @brief    Stove 약관 동의 페이지 표시용 Webview의 위치를 (operation != DEFAULT일 때 적용) 설정합니다.
                * @param    int32_t x Webview의 x축 위치
                * @param    int32_t y Webview의 y축 위치
                * @param    int32_t width Webview의 가로 길이
                * @param    int32_t height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Set the position of the Webview for displaying the Stove terms agreement page (applied when operation != DEFAULT).
                * @param    int32_t x x-axis position of the Webview
                * @param    int32_t y y-axis position of the Webview
                * @param    int32_t width width of the Webview
                * @param    int32_t height height of the Webview
                */
                void SetWebviewRect(int32_t x, int32_t y, int32_t width, int32_t height);

            public:
                StovePCTermsOption();
                StovePCTermsOption(const StovePCTermsOption& rhs);
                StovePCTermsOption(const StovePCTermsOptionCpp* rhs);
                ~StovePCTermsOption() = default;

                StovePCTermsOption& operator=(const StovePCTermsOption& rhs);
                StovePCTermsOption& operator=(const StovePCTermsOptionCpp* rhs);

            private:
                void DeepCopy(const StovePCTermsOption& rhs);
                void DeepCopy(const StovePCTermsOptionCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    IAP_FetchTermsAgreement API 수행 시 동작 방식 결정
                * \endkorean
                * \english
                * @brief    Determine the operation method when the IAP_FetchTermsAgreement API is executed
                * \endenglish
                */
                StovePCTermsOperation operation;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 결정
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    Determine the type when using the Stove Webview
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                Base::WebViewMode webviewMode;

                /*!
                * \korean
                * @brief    Stove 약관 동의 페이지 표시용 Webview의 x축 위치
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    x-axis position of the Webview for displaying the Stove terms agreement page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewPosX;

                /*!
                * \korean
                * @brief    Stove 약관 동의 페이지 표시용 Webview의 y축 위치 (operation != DEFAULT일 때 적용)
                * \endkorean
                * \english
                * @brief    y-axis position of the Webview for displaying the Stove terms agreement page (applied when operation != DEFAULT)
                * \endenglish
                */
                int32_t webviewPosY;

                /*!
                * \korean
                * @brief    Stove 약관 동의 페이지 표시용 Webview의 가로 길이 (operation != DEFAULT일 때 적용)
                * \endkorean
                * \english
                * @brief    Width of the Webview for displaying the Stove terms agreement page (applied when operation != DEFAULT)
                * \endenglish
                */
                int32_t webviewWidth;

                /*!
                * \korean
                * @brief    Stove 약관 동의 페이지 표시용 Webview의 세로 길이 (operation != DEFAULT일 때 적용)
                * \endkorean
                * \english
                * @brief    Height of the Webview for displaying the Stove terms agreement page (applied when operation != DEFAULT)
                * \endenglish
                */
                int32_t webviewHeight;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCPaymentOption
            * \korean
            * @brief IAP_StartPayment API에 대한 옵션을 전달하는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that delivers options for the IAP_StartPayment API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCPaymentOption
            {
            public:
                /*!
                * \korean
                * @brief    IAP_StartPayment 메소드 수행 시 동작 방식을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the operation method when the IAP_StartPayment method is executed.
                * \endenglish
                * @return   StovePCPaymentOperation operation
                */
                StovePCPaymentOperation GetOperation() const;

                /*!
                * \korean
                * @brief    IAP_StartPayment 메소드 수행 시 동작 방식을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the operation method when the IAP_StartPayment method is executed.
                * \endenglish
                * @param   StovePCPaymentOperation operation
                */
                void SetOperation(StovePCPaymentOperation operation);

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 (operation != DEFAULT일 때 적용) 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the type when using the Stove Webview (applied when operation != DEFAULT).
                * \endenglish
                * @return   Base::WebViewMode webviewMode
                */
                Base::WebViewMode GetWebviewMode() const;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 (operation != DEFAULT일 때 적용) 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the type when using the Stove Webview (applied when operation != DEFAULT).
                * \endenglish
                * @param    Base::WebViewMode webviewMode
                */
                void SetWebviewMode(Base::WebViewMode mode);

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 위치를 (operation != DEFAULT일 때 적용) 가져옵니다.
                * @param    __out int32_t* x Webview의 x축 위치
                * @param    __out int32_t* y Webview의 y축 위치
                * @param    __out int32_t* width Webview의 가로 길이
                * @param    __out int32_t* height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Check the position of the Webview for displaying the Stove payment page (applied when operation != DEFAULT).
                * @param    __out int32_t* x x-axis position of the Webview
                * @param    __out int32_t* y y-axis position of the Webview
                * @param    __out int32_t* width width of the Webview
                * @param    __out int32_t* height height of the Webview
                * \endenglish
                */
                void GetWebviewRect(__out int32_t* x, __out int32_t* y, __out int32_t* width, __out int32_t* height) const;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 위치를 (operation != DEFAULT일 때 적용) 설정합니다.
                * @param    int32_t x Webview의 x축 위치
                * @param    int32_t y Webview의 y축 위치
                * @param    int32_t width Webview의 가로 길이
                * @param    int32_t height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Set the position of the Webview for displaying the Stove payment page (applied when operation != DEFAULT).
                * @param    int32_t x x-axis position of the Webview
                * @param    int32_t y y-axis position of the Webview
                * @param    int32_t width width of the Webview
                * @param    int32_t height height of the Webview
                * \endenglish
                */
                void SetWebviewRect(int32_t x, int32_t y, int32_t width, int32_t height);

            public:
                StovePCPaymentOption();
                StovePCPaymentOption(const StovePCPaymentOption& rhs);
                StovePCPaymentOption(const StovePCPaymentOptionCpp* rhs);
                ~StovePCPaymentOption() = default;

                StovePCPaymentOption& operator=(const StovePCPaymentOption& rhs);
                StovePCPaymentOption& operator=(const StovePCPaymentOptionCpp* rhs);

            private:
                void DeepCopy(const StovePCPaymentOption& rhs);
                void DeepCopy(const StovePCPaymentOptionCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    IAP_StartPayment API 수행 시 동작 방식 결정
                * \endkorean
                * \english
                * @brief    Determine the operation method when the IAP_StartPayment API is executed
                * \endenglish
                */
                StovePCPaymentOperation operation;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 결정
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    Determine the type when using the Stove Webview
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                Base::WebViewMode webviewMode;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 x축 위치
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    x-axis position of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewPosX;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 y축 위치
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    y-axis position of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewPosY;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 가로 길이
                * @details  operation != DEFAULT일 때 적용
                * \endkorean
                * \english
                * @brief    Width of the Webview for displaying the Stove payment page (applied when operation != DEFAULT)
                * \endenglish
                */
                int32_t webviewWidth;

                /*!
                * \korean
                * @brief    Stove 결제 페이지 표시용 Webview의 세로 길이 (operation != DEFAULT일 때 적용)
                * \endkorean
                * \english
                * @brief    Height of the Webview for displaying the Stove payment page
                * @details  applied when operation != DEFAULT
                * \endenglish
                */
                int32_t webviewHeight;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCVoidedPurchase
            * \korean
            * @brief 환불 처리 정보를 전달하는 구조체입니다.
            * @details IAP_FetchVoidedPurchases 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief A structure that delivers refund processing information.
            * @details Used when delivering results to the IAP_FetchVoidedPurchases callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCVoidedPurchase
            {
            public:
                /*!
                * \korean
                * @brief    STOVE 빌링 시스템에서 발급한 주문번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the order number issued by the STOVE billing system.
                * \endenglish
                * @return   const int64_t tid
                */
                int64_t GetTid() const;

                /*!
                * \korean
                * @brief    마켓 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the market code.
                * \endenglish
                * @return   const wchar_t* marketCode
                */
                const wchar_t* GetMarketCode() const;

                /*!
                * \korean
                * @brief    STOVE 플랫폼에 등록한 상품 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product code registered on the STOVE platform.
                * \endenglish
                * @return   const wchar_t* productId
                */
                const wchar_t* GetProductId() const;

                /*!
                * \korean
                * @brief    마켓에 등록된 상품 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the product code registered on the market.
                * \endenglish
                * @return   const wchar_t* marketProductId
                */
                const wchar_t* GetMarketProductId() const;

                /*!
                * \korean
                * @brief   현재 게임의 사용자 ID를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the user ID of the current game.
                * \endenglish
                * @return   const wchar_t* userId
                */
                const wchar_t* GetUserId() const;

                /*!
                * \korean
                * @brief    STOVE 플랫폼에서 게임 캐릭터별로 발급되는 유일키를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the unique key issued for each game character on the STOVE platform.
                * \endenglish
                * @return   const int64_t characterNo
                */
                int64_t GetCharacterNo() const;

                /*!
                * \korean
                * @brief    UTC+0 기준의 결제시간을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the payment time based on UTC+0.
                * \endenglish
                * @return   const int64_t purchaseMillis
                */
                int64_t GetPurchaseMillis() const;

                /*!
                * \korean
                * @brief    UTC+0 기준의 환불 처리된 시간을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the time when the refund was processed based on UTC+0.
                * \endenglish
                * @return   const int64_t voidedMillis
                */
                int64_t GetVoidedMillis() const;

            public:
                StovePCVoidedPurchase();
                StovePCVoidedPurchase(const StovePCVoidedPurchase& rhs);
                StovePCVoidedPurchase(const StovePCVoidedPurchaseCpp* rhs);
                ~StovePCVoidedPurchase();

                StovePCVoidedPurchase& operator=(const StovePCVoidedPurchase& rhs);
                StovePCVoidedPurchase& operator=(const StovePCVoidedPurchaseCpp* rhs);

            private:
                void DeepCopy(const StovePCVoidedPurchase& rhs);
                void DeepCopy(const StovePCVoidedPurchaseCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    STOVE 빌링 시스템에서 발급한 주문번호
                * \endkorean
                * \english
                * @brief    Order number issued by the STOVE billing system
                * \endenglish
                */
                int64_t tid;

                /*!
                * \korean
                * @brief    마켓 코드
                * \endkorean
                * \english
                * @brief    Market code
                * \endenglish
                */
                wchar_t* marketCode = nullptr;

                /*!
                * \korean
                * @brief    STOVE 플랫폼에 등록한 상품 코드
                * \endkorean
                * \english
                * @brief    Product code registered on the STOVE platform
                * \endenglish
                */
                wchar_t* productId = nullptr;

                /*!
                * \korean
                * @brief    마켓에 등록된 상품 코드
                * \endkorean
                * \english
                * @brief    Product code registered on the market
                * \endenglish
                */
                wchar_t* marketProductId = nullptr;

                /*!
                * \korean
                * @brief    현재 게임의 사용자 ID
                * \endkorean
                * \english
                * @brief    User ID of the current game
                * \endenglish
                */
                wchar_t* userId = nullptr;

                /*!
                * \korean
                * @brief    STOVE 플랫폼에서 게임 캐릭터별로 발급되는 유일키
                * \endkorean
                * \english
                * @brief    Unique key issued for each game character on the STOVE platform
                * \endenglish
                */
                int64_t characterNo;

                /*!
                * \korean
                * @brief    UTC 기준의 결제시간
                * \endkorean
                * \english
                * @brief    Payment time based on UTC
                * \endenglish
                */
                int64_t purchaseMillis;

                /*!
                * \korean
                * @brief    UTC 기준의 환불 처리된 시간
                * \endkorean
                * \english
                * @brief    Time when the refund was processed based on UTC
                * \endenglish
                */
                int64_t voidedMillis;
            };
#pragma pack(pop)


            /*!
            * @struct StovePCVoidedPurchasesEx
            * \korean
            * @brief 환불 처리 정보를 전달하는 구조체입니다.
            * @details IAP_FetchVoidedPurchases 콜백에 결과 전달 시 사용합니다.
            * \endkorean
            * \english
            * @brief A structure that delivers refund processing information.
            * @details Used when delivering results to the IAP_FetchVoidedPurchases callback.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCVoidedPurchasesEx
            {
            public:
                /*!
                * \korean
                * @brief    STOVE 빌링 시스템에서 발급한 주문번호를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the order number issued by the STOVE billing system.
                * \endenglish
                * @return   const int64_t tid
                */
                int64_t GetTid() const;

                /*!
                * \korean
                * @brief    마켓 코드 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the market code value.
                * \endenglish
                * @return   const wchar_t* marketCode
                */
                wchar_t* GetMarketCode() const;

                /*!
                * \korean
                * @brief    STOVE 플랫폼 회원 번호 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the member number issued by the STOVE platform.
                * \endenglish
                * @return   const int64_t memberNo
                */
                int64_t GetMemberNo() const;

                /*!
                * \korean
                * @brief    STOVE 플랫폼 회원 guid 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the member guid issued by the STOVE platform.
                * \endenglish
                * @return   const wchar_t* guid
                */
                wchar_t* GetGuid() const;

                /*!
                * \korean
                * @brief    게임 캐릭터 별로 발급되는 유일키(STOVE에서 발급) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the unique key issued for each game character (issued by STOVE).
                * \endenglish
                * @return   const int64_t characterNo
                */
                int64_t GetCharacterNo() const;

                /*!
                * \korean
                * @brief    게임 내 아이템ID ( == product_id) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the item ID in the game ( == product_id).
                * \endenglish
                * @return   const wchar_t* inserviceItemId
                */
                wchar_t* GetInserviceItemId() const;

                /*!
                * \korean
                * @brief    마켓에 등록된 아이템 ID ( == market_product_id) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the item ID registered in the market ( == market_product_id).
                * \endenglish
                * @return   const wchar_t* marketItemId
                */
                wchar_t* GetMarketItemId() const;

                /*!
                * \korean
                * @brief    마켓 주문 번호 (모바일 마켓 미 제공(현재 STEAM 만 제공)) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the market order number (not provided for mobile markets (currently only STEAM is provided)).
                * \endenglish
                * @return   const wchar_t* marketTid
                */
                wchar_t* GetMarketTid() const;

                /*!
                * \korean
                * @brief    마켓 회원 아이디 (모바일 마켓 미 제공(현재 STEAM 만 제공)) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the market member ID (not provided for mobile markets (currently only STEAM is provided)).
                * \endenglish
                * @return   const wchar_t* marketUserId
                */
                wchar_t* GetMarketUserId() const;

                /*!
                * \korean
                * @brief    결제시간 (UTC) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the payment time (UTC).
                * \endenglish
                * @return   const int64_t purchaseDt
                */
                int64_t GetPurchaseDt() const;

                /*!
                * \korean
                * @brief    환불 처리된 시간 (UTC) 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the voided time (UTC).
                * \endenglish
                * @return   const int64_t voidedDt
                */
                int64_t GetVoidedDt() const;

            public:
                StovePCVoidedPurchasesEx();
                StovePCVoidedPurchasesEx(const StovePCVoidedPurchasesEx& rhs);
                StovePCVoidedPurchasesEx(const StovePCVoidedPurchasesExCpp* rhs);
                ~StovePCVoidedPurchasesEx();

                StovePCVoidedPurchasesEx& operator=(const StovePCVoidedPurchasesEx& rhs);
                StovePCVoidedPurchasesEx& operator=(const StovePCVoidedPurchasesExCpp* rhs);

            private:
                void DeepCopy(const StovePCVoidedPurchasesEx& rhs);
                void DeepCopy(const StovePCVoidedPurchasesExCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    STOVE 빌링 시스템에서 발급한 주문번호
                * \endkorean
                * \english
                * @brief    Order number issued by the STOVE billing system
                * \endenglish
                */
                int64_t tid = 0LL;

                /*!
                 * \korean
                 * @brief    마켓 코드
                 * \endkorean
                 * \english
                 * @brief    Market code
                 * \endenglish
                 */
                wchar_t* marketCode;

                /*!
                 * \korean
                 * @brief    STOVE 플랫폼 회원 번호
                 * \endkorean
                 * \english
                 * @brief    STOVE platform member number
                 * \endenglish
                 */
                int64_t memberNo = 0LL;

                /*!
                 * \korean
                 * @brief    STOVE 플랫폼 회원 guid
                 * \endkorean
                 * \english
                 * @brief    STOVE platform member guid
                 * \endenglish
                 */
                wchar_t* guid;

                /*!
                 * \korean
                 * @brief    게임 캐릭터 별로 발급되는 유일키(STOVE에서 발급)
                 * \endkorean
                 * \english
                 * @brief    Unique key issued for each game character (issued by STOVE)
                 * \endenglish
                 */
                int64_t characterNo = 0LL;

                /*!
                 * \korean
                 * @brief    게임 내 아이템ID ( == product_id)
                 * \endkorean
                 * \english
                 * @brief    Item ID in the game ( == product_id)
                 * \endenglish
                 */
                wchar_t* inserviceItemId;

                /*!
                 * \korean
                 * @brief    마켓에 등록된 아이템 ID ( == market_product_id)
                 * \endkorean
                 * \english
                 * @brief    Item ID registered in the market ( == market_product_id)
                 * \endenglish
                 */
                wchar_t* marketItemId;

                /*!
                 * \korean
                 * @brief    마켓 주문 번호 (모바일 마켓 미 제공(현재 STEAM 만 제공))
                 * \endkorean
                 * \english
                 * @brief    Market order number (not provided for mobile markets (currently only STEAM is provided))
                 * \endenglish
                 */
                wchar_t* marketTid;

                /*!
                 * \korean
                 * @brief    마켓 회원 아이디 (모바일 마켓 미 제공(현재 STEAM 만 제공))
                 * \endkorean
                 * \english
                 * @brief    Market member ID (not provided for mobile markets (currently only STEAM is provided))
                 * \endenglish
                 */
                wchar_t* marketUserId;

                /*!
                 * \korean
                 * @brief    결제시간 (UTC)
                 * \endkorean
                 * \english
                 * @brief    Payment time (UTC)
                 * \endenglish
                 */
                int64_t purchaseDt = 0LL;

                /*!
                 * \korean
                 * @brief    환불 처리된 시간 (UTC)
                 * \endkorean
                 * \english
                 * @brief    Voided time (UTC)
                 * \endenglish
                 */
                int64_t voidedDt = 0LL;

                /// Reserved fields for future extension
                uint64_t reserved1;
                uint64_t reserved2;
                uint64_t reserved3;
                uint64_t reserved4;
                uint64_t reserved5;
            };
#pragma pack(pop)


            /*!
            * @struct StovePCWithdrawGameOption
            * \korean
            * @brief IAP_WithdrawGame API에 대한 옵션을 전달하는 구조체입니다.
            * \endkorean
            * \english
            * @brief A structure that delivers options for the IAP_WithdrawGame API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCWithdrawGameOption
            {
            public:
                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the type when using the Stove Webview.
                * \endenglish
                * @return   Base::WebViewMode webviewMode
                */
                Base::WebViewMode GetWebviewMode() const;

                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the type when using the Stove Webview.
                * \endenglish
                * @param    Base::WebViewMode webviewMode
                */
                void SetWebviewMode(Base::WebViewMode mode);

                /*!
                * \korean
                * @brief    Stove 게임 탈퇴 페이지 표시용 Webview의 위치를 가져옵니다.
                * @param    __out int32_t* x Webview의 x축 위치
                * @param    __out int32_t* y Webview의 y축 위치
                * @param    __out int32_t* width Webview의 가로 길이
                * @param    __out int32_t* height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Get the position of the Webview for displaying the Stove game withdrawal page.
                * @param    __out int32_t* x x-axis position of the Webview
                * @param    __out int32_t* y y-axis position of the Webview
                * @param    __out int32_t* width width of the Webview
                * @param    __out int32_t* height height of the Webview
                * \endenglish
                */
                void GetWebviewRect(__out int32_t* x, __out int32_t* y, __out int32_t* width, __out int32_t* height) const;

                /*!
                * \korean
                * @brief    Stove 게임 탈퇴 페이지 표시용 Webview의 위치를 설정합니다.
                * @param    int32_t x Webview의 x축 위치
                * @param    int32_t y Webview의 y축 위치
                * @param    int32_t width Webview의 가로 길이
                * @param    int32_t height Webview의 세로 위치
                * \endkorean
                * \english
                * @brief    Set the position of the Webview for displaying the Stove game withdrawal page. (applied when operation != DEFAULT).
                * @param    int32_t x x-axis position of the Webview
                * @param    int32_t y y-axis position of the Webview
                * @param    int32_t width width of the Webview
                * @param    int32_t height height of the Webview
                */
                void SetWebviewRect(int32_t x, int32_t y, int32_t width, int32_t height);

            public:
                StovePCWithdrawGameOption();
                StovePCWithdrawGameOption(const StovePCWithdrawGameOption& rhs);
                StovePCWithdrawGameOption(const StovePCWithdrawGameOptionCpp* rhs);
                ~StovePCWithdrawGameOption() = default;

                StovePCWithdrawGameOption& operator=(const StovePCWithdrawGameOption& rhs);
                StovePCWithdrawGameOption& operator=(const StovePCWithdrawGameOptionCpp* rhs);

            private:
                void DeepCopy(const StovePCWithdrawGameOption& rhs);
                void DeepCopy(const StovePCWithdrawGameOptionCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    Stove Webview 사용 시 타입을 결정
                * \endkorean
                * \english
                * @brief    Determine the type when using the Stove Webview
                * \endenglish
                */
                Base::WebViewMode webviewMode;

                /*!
                * \korean
                * @brief    Stove 게임 탈퇴 페이지 표시용 Webview의 x축 위치
                * \endkorean
                * \english
                * @brief    x-axis position of the Webview for displaying the Stove game withdrawal page
                * \endenglish
                */
                int32_t webviewPosX;

                /*!
                * \korean
                * @brief    Stove 게임 탈퇴 페이지 표시용 Webview의 y축 위치
                * \endkorean
                * \english
                * @brief    y-axis position of the Webview for displaying the Stove game withdrawal page
                * \endenglish
                */
                int32_t webviewPosY;

                /*!
                * \korean
                * @brief    Stove 게임 탈퇴 페이지 표시용 Webview의 가로 길이
                * \endkorean
                * \english
                * @brief    Width of the Webview for displaying the Stove game withdrawal page
                * \endenglish
                */
                int32_t webviewWidth;

                /*!
                * \korean
                * @brief    Stove 게임 탈퇴 페이지 표시용 Webview의 세로 길이
                * \endkorean
                * \english
                * @brief    Height of the Webview for displaying the Stove game withdrawal page
                * \endenglish
                */
                int32_t webviewHeight;
            };
#pragma pack(pop)
        }
    }
}
