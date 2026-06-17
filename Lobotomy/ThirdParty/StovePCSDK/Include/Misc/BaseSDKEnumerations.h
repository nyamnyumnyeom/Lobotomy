#pragma once

/*!
    * @file     Enumerations.h
    * \korean
    * @brief    BaseSDK에서 사용하는 Enumerations 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Enumerations values used in BaseSDK.
    * \endenglish
*/

#include <stdint.h>

namespace Stove
{
    namespace PCSDK
    {
        namespace Base
        {
            /*!
            * @enum class StoveLanguage
            * \korean
            * @brief 언어 설정을 위한 enum 값 입니다.
            * \endkorean
            * \english
            * @brief Enum value for language settings.
            * \endenglish
            */
            enum class StoveLanguage : uint32_t
            {
                /// System
                system = 0,

                /// English
                en = 1,

                /// Korean
                ko = 2,

                /// Japanese
                ja = 3,

                /// Chinese (Simplified, People's Republic of China)
                zh_cn = 4,

                /// Chinese (Traditional, Taiwan)
                zh_tw = 5,

                /// German
                de = 6,

                /// French
                fr = 7,

                /// Spanish, Castilian
                es = 8,

                /// Portuguese
                pt = 9,

                /// Thai
                th = 10,

                /// Vietnamese
                vi = 11,
            };

            /*!
            * @enum class StoveOverlayState
            * \korean
            * @brief 오버레이 표시 상태를 위한 enum 값입니다.
            * \endkorean
            * \english
            * @brief Enum values for overlay display state.
            * \endenglish
            */
            enum class StoveOverlayState : uint32_t
            {
                /*!
                * \korean
                * @brief 오버레이를 표시합니다.
                * \endkorean
                * \english
                * @brief Show overlay
                * \endenglish
                */
                SHOW = 0,

                /*!
                * \korean
                * @brief 오버레이를 숨깁니다.
                * \endkorean
                * \english
                * @brief Hide overlay
                * \endenglish
                */
                HIDE = 1,

                /*!
                * \korean
                * @brief 오버레이를 확장합니다.
                * \endkorean
                * \english
                * @brief Expand overlay
                * \endenglish
                */
                EXPANDED = 2,
            };

            /*!
            * @enum class OverlaySeverity
            * \korean
            * @brief 오버레이 심각도를 위한 enum 값입니다.
            * \endkorean
            * \english
            * @brief Enum values for overlay severity.
            * \endenglish
            */
            enum class OverlaySeverity : uint32_t
            {
                /*!
                * \korean
                * @brief 일반 심각도 
                * \endkorean
                * \english
                * @brief Normal severity 
                * \endenglish
                */
                STOVEAPI_OVERLAY_SEVERITY_NORMAL = 0,

                /*!
                * \korean
                * @brief 경고 심각도  
                * \endkorean
                * \english
                * @brief Warning severity 
                * \endenglish
                */
                STOVEAPI_OVERLAY_SEVERITY_WARNING = 1,
            };

            /*!
            * @enum class WebViewMode
            * \korean
            * @brief 언어 설정을 위한 enum 값 입니다.
            * \endkorean
            * \english
            * @brief Enum value for language settings.
            * \endenglish
            */
            enum class WebViewMode : uint32_t
            {
                /*!
                * \korean
                * @brief WebView가 External Mode로 실행됩니다.
                * \endkorean
                * \english
                * @brief WebView is executed in External Mode.
                * \endenglish
                */
                EXTERNAL = 0,

                /*!
                * \korean
                * @brief WebView가 Internal Mode로 실행됩니다.
                * \endkorean
                * \english
                * @brief WebView is executed in Internal Mode.
                * \endenglish
                */
                INTERNAL,

                /*!
                * \korean
                * WebViewMode의 끝을 나타내는 값이며 유효한 값이 아닙니다.
                * \endkorean
                * \english
                * The end of WebViewMode, and it is not a valid Value.
                * \endenglish
                */
                _MAX_COUNT
            };
        }
    }
}
