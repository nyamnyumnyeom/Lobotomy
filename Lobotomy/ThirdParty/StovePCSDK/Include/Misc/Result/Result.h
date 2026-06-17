#pragma once

/*!
* @file     Result.h
* \korean
* @brief    PCSDK3에서 사용하는 공통된 Return 값의 헤더 파일입니다.
* \endkorean
* \english
* @brief    Header file of common return values used in PCSDK3.
* \endenglish
*/

#include <stdint.h>
#include <type_traits>

#include "../SDKExports.h"

namespace Stove
{
    namespace PCSDK
    {
        struct ResultCpp;
        struct CallbackResultCpp;

        /*!
        * @struct Result
        * \korean
        * @brief Stove PCSDK 3.x에서 기본 API 호출시 전달받는 구조체입니다.
        * \endkorean
        * \english
        * @brief Structure received when calling the basic API in Stove PCSDK 3.x.
        * \endenglish
        */
#pragma pack(push, 4)
        struct SDK_EXPORTS Result
        {
        public:
            /*!
            * \korean
            * @brief    API의 성공 여부를 가져올 수 있다.
            * @return   bool API의 성공 여부
            * \endkorean
            * \english
            * @brief    Get the success of the API.
            * @return   bool API success
            * \endenglish
            */
            bool IsSuccessful() const;

            /*!
            * \korean
            * @brief    SDK의 이름을 가져올 수 있다.
            * @return   std::wstring SDK의 이름
            * \endkorean
            * \english
            * @brief    You can Get the name of the SDK.
            * @return   std::wstring SDK name
            * \endenglish
            */
            const wchar_t* GetSDKName() const;

            /*!
            * \korean
            * @brief    함수의 Code 값을 가져올 수 있다.
            * @return   uint32_t Method Code
            * \endkorean
            * \english
            * @brief    You can get the code of the function.
            * @return   uint32_t Method Code
            * \endenglish
            */
            uint32_t GetMethodCode() const;

            /*!
            * \korean
            * @brief    함수의 Result Code 값을 가져올 수 있다.
            * @return   uint32_t Result Code
            * \endkorean
            * \english
            * @brief    You can get the Result Code of the function.
            * @return   uint32_t Result Code
            * \endenglish
            */
            uint32_t GetResultCode() const;

        public:
            Result();
            Result(const PCSDK::Result& rhs);
            Result(const PCSDK::ResultCpp* rhs);
            ~Result();

            Result& operator=(const PCSDK::Result& rhs);
            Result& operator=(const PCSDK::ResultCpp* rhs);

        private:
            void DeepCopy(const PCSDK::Result& rhs);
            void DeepCopy(const PCSDK::ResultCpp* rhs);

            wchar_t* sdkName = nullptr;
            uint32_t methodCode = 0x01U;
            uint32_t resultCode = 0xFFU;
        };
#pragma pack(pop)

        /*!
        * @struct CallbackResult
        * \korean
        * @brief Stove PCSDK 3.x에서 Callback 호출시 전달받는 구조체입니다.
        * \endkorean
        */
#pragma pack(push, 4)
        struct SDK_EXPORTS CallbackResult
        {
        public:
            /*!
            * \korean
            * @brief    함수의 API 결과 값을 가져옵니다.
            * @return   Result result
            * \endkorean
            * \english
            * @brief    Get the API result value of the function.
            * @return   Result result
            * \endenglish
            */
            Result GetResult() const;

            /*!
            * \korean
            * @brief    함수의 API 에러 메세지를 가져옵니다.
            * @return   const wchar_t* errorMessage
            * \endkorean
            * \english
            * @brief    Get the API error message of the function.
            * @return   const wchar_t* errorMessage
            * \endenglish
            */
            const wchar_t* GetErrorMessage() const;

            /*!
            * \korean
            * @brief    외부에서 발생한 Error 를 가져옵니다.
            * @return   uint32_t externalError
            * \endkorean
            * \english
            * @brief    Get the error that occurred externally.
            * @return   uint32_t externalError
            * \endenglish
            */
            int32_t GetExternalError() const;


        public:
            CallbackResult();
            CallbackResult(const CallbackResult& rhs);
            CallbackResult(const CallbackResultCpp* rhs);
            CallbackResult(uint64_t callerIdentifier, const CallbackResultCpp* rhs);
            ~CallbackResult();

            CallbackResult& operator=(const CallbackResult& rhs);
            CallbackResult& operator=(const CallbackResultCpp* rhs);

        public:
            void DeepCopy(const CallbackResult& rhs);
            void DeepCopy(const CallbackResultCpp* rhs);


        public:
            /*! \korean
            * Error 에 대한 유형 결과값
            * \endkorean
            * \english
            * Type result value for Error
            * \endenglish
            */ 
            Result result;

            /*!
            * \korean
            * Error가 발생한 이유에 대한 상세 메세지
            * \endkorean
            * \english
            * Detailed message about why the error occurred
            * \endenglish
            */
            wchar_t* errorMessage = nullptr;

            /*!
            * \korean
            * 외부에서 발생한 Error 값 (HTTP error or API result code)
            * \endkorean
            * \english
            * External error value (HTTP error or API result code)
            * \endenglish
            */
            int32_t externalError;

            /*!
            * \korean
            * 호출자에 대한 Identifier
            * \endkorean
            * \english
            * Identifier for the caller
            * \endenglish
            */
            uint64_t callerIdentifier;
        };
#pragma pack(pop)
    }
}