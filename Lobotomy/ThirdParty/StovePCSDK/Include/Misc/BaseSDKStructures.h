#pragma once

/*!
* @file     Structures.h
* \korean
* @brief    BaseSDK에서 사용하는 Structures 값의 헤더 파일입니다.
* \endkorean
* \english
* @brief    Header file of Structures values used in BaseSDK.
* \endenglish
*/

#include <string>

#include "BaseSDKEnumerations.h"
#include "BaseSDKResult.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Base
        {
            struct StovePCInitializeParamCpp;
            struct StovePCInitializeParamEx2Cpp;
            struct StovePCTokenCpp;
            struct StovePCUserCpp;
            struct StovePCGdsCpp;
            struct StovePCSigninCpp;
            struct StovePCOverImmersionCpp;
            struct StovePCShutdownCpp;
            struct StovePCTraceHintCpp;
            struct StovePCGameProfileCpp;
            struct StovePCVietnamAgeRatingInfoCpp;
            struct StovePCVietnamOverimmersionInfoCpp;

            /*!
            * @struct StovePCInitializeParam
            * \korean
            * @brief Base_Initialize API를 호출할 때 전달하는 구조체 입니다.
            * \endkorean
            * \english
            * @brief Structure to be passed when calling the Base_Initialize API.
            * \endenglish
            */
            struct SDK_EXPORTS StovePCInitializeParam
            {
            public:
                /*!
                * \korean
                * @brief    Stove Environment 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove Environment value.
                * \endenglish
                * @return   const wchar_t*    environment
                */
                const wchar_t* GetEnvironment() const;

                /*!
                * \korean
                * @brief    Stove Environment 값을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the Stove Environment value.
                * \endenglish
                * @param[in] const wchar_t*    env
                */
                void SetEnvironment(const wchar_t* env);

                /*!
                * \korean
                * @brief    Stove Game ID 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove Game ID value.
                * \endenglish
                * @return   const wchar_t*    gameId
                */
                const wchar_t* GetGameID() const;

                /*!
                * \korean
                * @brief    Stove Game ID 값을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the Stove Game ID value.
                * \endenglish
                * @param[in] const wchar_t*    gameId
                */
                void SetGameID(const wchar_t* gameId);

                /*!
                * \korean
                * @brief    Stove Application key 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove Application key value.
                * \endenglish
                * @return   const wchar_t*    applicationKey
                */
                const wchar_t* GetApplicationKey() const;

                /*!
                * \korean
                * @brief    Stove Application key 값을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the Stove Application key value.
                * \endenglish
                * @param[in] const wchar_t*    appKey
                */
                void SetApplicationKey(const wchar_t* appKey);

            public:
                StovePCInitializeParam();
                StovePCInitializeParam(const StovePCInitializeParam& rhs);
                StovePCInitializeParam(const StovePCInitializeParamCpp* rhs);
                ~StovePCInitializeParam();

                StovePCInitializeParam& operator=(const StovePCInitializeParam& rhs);
                StovePCInitializeParam& operator=(const StovePCInitializeParamCpp* rhs);

            private:
                void DeepCopy(const StovePCInitializeParam& rhs);
                void DeepCopy(const StovePCInitializeParamCpp* rhs);

            private:
                /// Stove Environment Value
                wchar_t* environment;

                /// Stove Game ID Value
                wchar_t* gameId;

                /// Stove Application Key Value
                wchar_t* applicationKey;
            };

            /*!
            * @struct StovePCInitializeParamEx2
            * \korean
            * @brief Base_RestartAppIfNecessaryAsyncEx API를 호출할 때 전달하는 구조체 입니다.
            * \endkorean
            * \english
            * @brief Structure to be passed when calling the Base_Initialize API.
            * \endenglish
            */
            struct SDK_EXPORTS StovePCInitializeParamEx2
            {
            public:
                /*!
                * \korean
                * @brief    Stove Environment 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove Environment value.
                * \endenglish
                * @return   const wchar_t*    environment
                */
                const wchar_t* GetEnvironment() const;

                /*!
                * \korean
                * @brief    Stove Environment 값을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the Stove Environment value.
                * \endenglish
                * @param[in] const wchar_t*    env
                */
                void SetEnvironment(const wchar_t* env);

                /*!
                * \korean
                * @brief    Stove Game ID 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove Game ID value.
                * \endenglish
                * @return   const wchar_t*    gameId
                */
                const wchar_t* GetGameID() const;

                /*!
                * \korean
                * @brief    Stove Game ID 값을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the Stove Game ID value.
                * \endenglish
                * @param[in] const wchar_t*    gameId
                */
                void SetGameID(const wchar_t* gameId);

                /*!
                * \korean
                * @brief    Stove Application key 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove Application key value.
                * \endenglish
                * @return   const wchar_t*    applicationKey
                */
                const wchar_t* GetApplicationKey() const;

                /*!
                * \korean
                * @brief    Stove Application key 값을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the Stove Application key value.
                * \endenglish
                * @param[in] const wchar_t*    appKey
                */
                void SetApplicationKey(const wchar_t* appKey);

                /*!
                * \korean
                * @brief    대기 시간(밀리초)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the wait time in milliseconds.
                * \endenglish
                * @return   uint32_t    waitTimeMillisec
                */
                uint32_t GetWaitTimeMillisec() const;

                /*!
                * \korean
                * @brief    대기 시간(밀리초)을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the wait time in milliseconds.
                * \endenglish
                * @param[in] uint32_t    waitTime
                */
                void SetWaitTimeMillisec(uint32_t waitTime);

                /*!
                * \korean
                * @brief    런처 실행 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get whether to launch the launcher.
                * \endenglish
                * @return   bool    launchLauncher
                */
                bool GetLaunchLauncher() const;

                /*!
                * \korean
                * @brief    런처 실행 여부를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set whether to launch the launcher.
                * \endenglish
                * @param[in] bool    launch
                */
                void SetLaunchLauncher(bool launch);

                /*!
                * \korean
                * @brief    플랫폼 이름을 가져옵니다.
                * @details  Stove, Steam...
                * \endkorean
                * \english
                * @brief    Get the platform name.
                * @details  Stove, Steam...
                * \endenglish
                * @return   const wchar_t*    platformName
                */
                const wchar_t* GetPlatformName() const;

                /*!
                * \korean
                * @brief    플랫폼 이름을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the platform name.
                * \endenglish
                * @param[in] const wchar_t*    platformName
                */
                void SetPlatformName(const wchar_t* platformName);

            public:
                StovePCInitializeParamEx2();
                StovePCInitializeParamEx2(const StovePCInitializeParamEx2& rhs);
                StovePCInitializeParamEx2(const StovePCInitializeParamEx2Cpp* rhs);
                ~StovePCInitializeParamEx2();

                StovePCInitializeParamEx2& operator=(const StovePCInitializeParamEx2& rhs);
                StovePCInitializeParamEx2& operator=(const StovePCInitializeParamEx2Cpp* rhs);

            private:
                void DeepCopy(const StovePCInitializeParamEx2& rhs);
                void DeepCopy(const StovePCInitializeParamEx2Cpp* rhs);

            private:
                /// Stove Environment Value
                wchar_t* environment;

                /// Stove Game ID Value
                wchar_t* gameId;

                /// Stove Application Key Value
                wchar_t* applicationKey;

                /// Wait time in milliseconds
                uint32_t waitTimeMillisec;

                /// Whether to launch the launcher
                bool launchLauncher;

                /// Platform name
                wchar_t* platformName;

                /// Reserved fields for future extension
                uint64_t reserved1;
                uint64_t reserved2;
                uint64_t reserved3;
                uint64_t reserved4;
                uint64_t reserved5;
            };

            /*!
            * @struct StovePCToken
            * \korean
            * @brief Base_AccessTokenRenewed API 호출시 응답받는 콜백의 Token 구조체입니다.
            * \endkorean
            * \english
            * @brief Token structure of the callback received when calling the Base_AccessTokenRenewed API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCToken
            {
            public:
                /*!
                * \korean
                * @brief    Stove AccessToken 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove AccessToken value.
                * \endenglish
                * @return   const wchar_t*    accessToken
                */
                const wchar_t* GetAccessToken() const;

                /*!
                * \korean
                * @brief    AccessToken의 남은 만료 시간(초)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the remaining expiration time (seconds) of AccessToken.
                * \endenglish
                * @return   int32_t    expire_in
                */
                int32_t GetExpireIn() const;

            public:
                StovePCToken();
                StovePCToken(const StovePCToken& rhs);
                StovePCToken(const StovePCTokenCpp* rhs);
                ~StovePCToken();

                StovePCToken& operator=(const StovePCToken& rhs);
                StovePCToken& operator=(const StovePCTokenCpp* rhs);

            private:
                void DeepCopy(const StovePCToken& rhs);
                void DeepCopy(const StovePCTokenCpp* rhs);

                /// Stove AccessToken Value
                wchar_t* accessToken = nullptr;

                /*!
                * \korean
                * @brief    Stove AccessToken의 남은 유효 시간 (초)
                * \endkorean
                * \english
                * @brief    Remaining validity period of Stove AccessToken (second)
                * \endenglish
                */
                int32_t expireIn;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCUser
            * \korean
            * @brief Base_GetUser API 호출시 전달받는 User 정보에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of User information received when calling the Base_GetUser API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCUser
            {
            public:
                /*!
                * \korean
                * @brief    런처에서 로그인한 유저의 스토브 회원번호를 가져옵니다.
                * @details  Deprecated 될 예정입니다. GetGameUserId()를 사용해주세요.
                * \endkorean
                * \english
                * @brief    Get the Stove member number of the user logged in from the launcher.
                * @details  It will be deprecated. Please use GetGameUserId().
                * \endenglish
                * @return   uint64_t     memberNumber
                */
                uint64_t GetMemberNumber() const;

                /*!
                * \korean
                * @brief    런처에서 로그인한 유저의 스토브 닉네임을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stove nickname of the user logged in from the launcher.
                * \endenglish
                * @return   const wchar_t* nickname
                */
                const wchar_t* GetNickname() const;

                /*!
                * \korean
                * @brief    런처에서 로그인한 유저의 gameUserId을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the gameUserId of the user logged in from the launcher.
                * \endenglish
                * @return   uint64_t gameUserId
                */
                uint64_t GetGameUserId() const;

            public:
                StovePCUser();
                StovePCUser(const StovePCUser& rhs);
                StovePCUser(const StovePCUserCpp* rhs);
                ~StovePCUser();

                StovePCUser& operator=(const StovePCUser& rhs);
                StovePCUser& operator=(const StovePCUserCpp* rhs);

            private:
                void DeepCopy(const StovePCUser& rhs);
                void DeepCopy(const StovePCUserCpp* rhs);

                /*!
                * \korean
                * @brief    런처에서 로그인한 유저의 스토브 회원번호
                * \endkorean
                * \english
                * @brief    Stove member number of the user logged in from the launcher
                * \endenglish
                */
                uint64_t memberNumber;

                /*!
                * \korean
                * @brief    런처에서 로그인한 유저의 스토브 닉네임
                * \endkorean
                * \english
                * @brief    Stove nickname of the user logged in from the launcher
                * \endenglish
                */
                wchar_t* nickname = nullptr;

                /*!
                * \korean
                * @brief    런처에서 로그인한 유저의 gameUserId
                * \endkorean
                * \english
                * @brief    gameUserId of the user logged in from the launcher
                * \endenglish
                */
                uint64_t gameUserId;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCGds
            * \korean
            * @brief Base_GetGds API 호출시 전달받는 User 정보에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of User information received when calling the Base_GetGds API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCGds
            {
            public:
                /*!
                * \korean
                * @brief    Stove 플렛폼 상에서 IP 주소를 통해 국가코드를 정상 처리한 경우 또는 국가코드를 정상 처리했으나 타임존을 처리하지 못한 경우 false로 반환합니다. true일 경우 국가코드를 기본값으로 처리합니다.
                * \endkorean
                * \english
                * @brief    If the login country code cannot be determined by IP, it is returned as the default country code of STOVE. In this case, if the isDefault value is true, if it is a country code confirmed by IP, isDefault is false.
                * \endenglish
                * @return   bool     isDefault
                */
                bool IsDefault() const;

                /*!
                * \korean
                * @brief    로그인한 국가코드 정보를 가져옵니다. ISO 3166-1 ALPHA-2 CODE 에 해당하는 국가코드를 반환합니다.
                * \endkorean
                * \english
                * @brief    Get the login country code information
                * \endenglish
                * @return   const wchar_t* nation
                */
                const wchar_t* GetNation() const;

                /*!
                * \korean
                * @brief    GDPR 규제적용 국가에 해당할 경우 규제적용 국가명칭을 반환합니다.
                * \endkorean
                * \english
                * @brief    Get the regulation name applied by the login country code
                * \endenglish
                * @return   const wchar_t* regulation
                */
                const wchar_t* GetRegulation() const;

                /*!
                * \korean
                * @brief    타임존 ID로 잘 알려진 IANA Time Zone Database (TZDB) 기준 ID를 반환합니다.
                * \endkorean
                * \english
                * @brief    Get the login timezone information
                * \endenglish
                * @return   const wchar_t* timeZone
                */
                const wchar_t* GetTimeZone() const;

                /*!
                * \korean
                * @brief    타임존 ID 기준으로 UTC 옵셋정보를 분단위로 반환합니다.
                * \endkorean
                * \english
                * @brief    Get the login timezone utc offset information
                * \endenglish
                * @return   int32_t utcOffset
                */
                int32_t GetUtcOffset() const;

                /*!
                * \korean
                * @brief    ISO 639-1 ALPHA-2 CODE를 기준으로 언어코드를 반환합니다. 중국어와 인도네시아어에 한하여 간체(zh), 번체(zh-tw), 인도네시아어(in)으로 반환합니다.
                * \endkorean
                * \english
                * @brief    Get the login language information
                * \endenglish
                * @return   const wchar_t* language
                */
                const wchar_t* GetLanguage() const;

            public:
                StovePCGds();
                StovePCGds(const StovePCGds& rhs);
                StovePCGds(const StovePCGdsCpp* rhs);
                ~StovePCGds();

                StovePCGds& operator=(const StovePCGds& rhs);
                StovePCGds& operator=(const StovePCGdsCpp* rhs);

            private:
                void DeepCopy(const StovePCGds& rhs);
                void DeepCopy(const StovePCGdsCpp* rhs);

                /*!
                * \korean
                * @brief    로그인한 국가코드가 IP로 판별 불가능할 경우 STOVE 기본 국가코드로 회신된다. 이럴 경우 isDefault 값은 true이며 IP로 확인된 국가코드일 경우 isDefault는 false이다.
                * \endkorean
                * \english
                * @brief    If the login country code cannot be determined by IP, it is returned as the default country code of STOVE. In this case, if the isDefault value is true, if it is a country code confirmed by IP, isDefault is false.
                * \endenglish
                */
                bool isDefault;

                /*!
                * \korean
                * @brief    로그인한 국가코드 정보
                * \endkorean
                * \english
                * @brief    Login country code information
                * \endenglish
                */
                wchar_t* nation;

                /*!
                * \korean
                * @brief    로그인한 국가 코드별 적용 규제명
                * \endkorean
                * \english
                * @brief    Regulation name applied by the login country code
                * \endenglish
                */
                wchar_t* regulation;

                /*!
                * \korean
                * @brief    로그인한 timezone 정보
                * \endkorean
                * \english
                * @brief    Login timezone information
                * \endenglish
                */
                wchar_t* timeZone;

                /*!
                * \korean
                * @brief    로그인한 timezone utc offset 정보
                * \endkorean
                * \english
                * @brief    Login timezone utc offset information
                * \endenglish
                */
                int32_t utcOffset;

                /*!
                * \korean
                * @brief    로그인한 언어 정보
                * \endkorean
                * \english
                * @brief    Login language information
                * \endenglish
                */
                wchar_t* language;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCSignin
            * \korean
            * @brief Base_GetSignin API 호출시 전달받는 Signin 정보에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of Signin information received when calling the Base_GetSignin API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCSignin
            {
            public:
                /*!
                * \korean
                * @brief    본인인증을 진행했는지 여부
                * \endkorean
                * \english
                * @brief    Get the person verification status.
                * \endenglish
                * @return   bool    personVerify
                */
                bool GetPersonVerify() const;

                /*!
                * \korean
                * @brief    이메일인증을 진행했는지 여부
                * \endkorean
                * \english
                * @brief    Get the email verification status.
                * \endenglish
                * @return   bool    emailVerify
                */
                bool GetEmailVerify() const;

                /*!
                * \korean
                * @brief    Stove 플렛폼 가입국가코드 (ISO 3166-1 ALPHA-2 CODE)
                * \endkorean
                * \english
                * @brief    Get the country of registration.
                * \endenglish
                * @return   const wchar_t* nationality
                */
                const wchar_t* GetNationality() const;

                /*!
                * \korean
                * @brief    IDP(Identity Provider) 구분코드. Stove 로그인 시점에 사용한 인증방법을 의미합니다.
                * @detail   SO: Stove 이메일 아이디 (온라인), FB : 페이스북, TW: 트위터, NAVER : 네이버,
                        GP : 구글, APPLE : 애플, SAO: 일회용 번호, QR: QR코드 로그인, RT: PC클라이언트기반 자동 로그인, LINE : 라인, STEAM : 스팀
                * \endkorean
                * \english
                * @brief    Get the account type.
                * \endenglish
                * @return   const wchar_t* providerCode
                */
                const wchar_t* GetProviderCode() const;

                /*!
                * \korean
                * @brief    계정타입코드
                * @detail   2: FACEBOOK, 3:TWITTER, 6:네이버, 9:구글플러스, 11: Stove PC회원가입, 12:애플, 13:라인, 14:라인게임즈, 15:스팀
                * \endkorean
                * \english
                * @brief    Get the account type.
                * \endenglish
                * @return   int accountType
                */
                int GetAccountType() const;

            public:
                StovePCSignin();
                StovePCSignin(const StovePCSignin& rhs);
                StovePCSignin(const StovePCSigninCpp* rhs);
                ~StovePCSignin();

                StovePCSignin& operator=(const StovePCSignin& rhs);
                StovePCSignin& operator=(const StovePCSigninCpp* rhs);

            private:
                void DeepCopy(const StovePCSignin& rhs);
                void DeepCopy(const StovePCSigninCpp* rhs);

                bool personVerify;
                bool emailVerify;
                wchar_t* nationality;
                wchar_t* providerCode;
                int accountType;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCOverImmersion
            * \korean
            * @brief Base_OverImmersionNotification API 호출시 전달받는 과몰입방지에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure for preventing over-immersion received when calling the Base_OverImmersionNotification API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCOverImmersion
            {
            public:
                /*!
                * \korean
                * @brief    과몰입 경고 메세지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the over-immersion warning message.
                * \endenglish
                * @return   const wchar_t* warningMessage
                */
                const wchar_t* GetWarningMessage() const;

                /*!
                * \korean
                * @brief    게임 경과시간(시간)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game elapsed time (hours).
                * \endenglish
                * @return   int32_t elapsedTimeInHours
                */
                int32_t GetElapsedTimeInHours() const;

                /*!
                * \korean
                * @brief    메세지 최소 노출시간(초)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the minimum exposure time of the message (seconds).
                * \endenglish
                * @return   int32_t minExposureTimeInSeconds
                */
                int32_t GetMinExposureTimeInSeconds() const;

            public:
                StovePCOverImmersion();
                StovePCOverImmersion(const StovePCOverImmersion& rhs);
                StovePCOverImmersion(const StovePCOverImmersionCpp* rhs);
                ~StovePCOverImmersion();

                StovePCOverImmersion& operator=(const StovePCOverImmersion& rhs);
                StovePCOverImmersion& operator=(const StovePCOverImmersionCpp* rhs);

            private:
                void DeepCopy(const StovePCOverImmersion& rhs);
                void DeepCopy(const StovePCOverImmersionCpp* rhs);

                /*!
                * \korean
                * @brief    과몰입 경고 메세지
                * \endkorean
                * \english
                * @brief    Over-immersion warning message
                * \endenglish
                */
                wchar_t* warningMessage = nullptr;

                /*!
                * \korean
                * @brief    게임 경과시간(시간)
                * \endkorean
                * \english
                * @brief    Game elapsed time (hours)
                * \endenglish
                */
                int32_t elapsedTimeInHours;

                /*!
                * \korean
                * @brief    메세지 최소 노출시간(초)
                * \endkorean
                * \english
                * @brief    Minimum exposure time of the message (seconds)
                * \endenglish
                */
                int32_t minExposureTimeInSeconds;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCShutdown
            * \korean
            * @brief Base_ShutdownNotification API 호출시 전달받는 셧다운에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure for shutdown received when calling the Base_ShutdownNotification API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCShutdown
            {
            public:
                /*!
                * \korean
                * @brief    사용자의 셧다운까지 남은 시간(분)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the remaining time (minutes) until the user's shutdown.
                * \endenglish
                * @return   int32_t inadvanceTimeInMinutes
                */
                int32_t GetInadvanceTimeInMinutes() const;

                /*!
                * \korean
                * @brief    셧다운 알림 메세지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the shutdown notification message.
                * \endenglish
                * @return   const wchar_t* shutdownMessage
                */
                const wchar_t* GetShutdownMessage() const;

                /*!
                * \korean
                * @brief    메세지 노출 시간(초)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the message exposure time (seconds).
                * \endenglish
                * @return   int32_t exposureTimeInSeconds
                */
                int32_t GetExposureTimeInSeconds() const;

            public:
                StovePCShutdown();
                StovePCShutdown(const StovePCShutdown& rhs);
                StovePCShutdown(const StovePCShutdownCpp* rhs);
                ~StovePCShutdown();

                StovePCShutdown& operator=(const StovePCShutdown& rhs);
                StovePCShutdown& operator=(const StovePCShutdownCpp* rhs);

            private:
                void DeepCopy(const StovePCShutdown& rhs);
                void DeepCopy(const StovePCShutdownCpp* rhs);

                /*!
                * \korean
                * @brief    사용자의 셧다운까지 남은 시간(분)
                * \endkorean
                * \english
                * @brief    Remaining time (minutes) until the user's shutdown
                * \endenglish
                */
                int32_t inadvanceTimeInMinutes;

                /*!
                * \korean
                * @brief    셧다운 알림 메세지
                * \endkorean
                * \english
                * @brief    Shutdown notification message
                * \endenglish
                */
                wchar_t* shutdownMessage = nullptr;

                /*!
                * \korean
                * @brief    메세지 노출 시간(초)
                * \endkorean
                * \english
                * @brief    Message exposure time (seconds)
                * \endenglish
                */
                int32_t exposureTimeInSeconds;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCTraceHint
            * \korean
            * @brief Base_GetTraceHint API 호출시 전달받는 스토브 플랫폼 로그를 추적하기 위한 단서에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of the clue for tracking Stove platform logs received when calling the Base_GetTraceHint API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCTraceHint
            {
            public:
                /*!
                * \korean
                * @brief    PCSDK가 초기화 될 때마다 발급되는 세션 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the session ID issued each time the PCSDK is initialized.
                * \endenglish
                * @return   const wchar_t* sessionId
                */
                const wchar_t* GetSessionId() const;

                /*!
                * \korean
                * @brief    레퍼런스(런처 또는 SGA)가 실행될 때마다 발급되는 세션 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the session ID issued each time the reference (launcher or SGA) is executed.
                * \endenglish
                * @return   const wchar_t* refSessionId
                */
                const wchar_t* GetRefSessionId() const;

                /*!
                * \korean
                * @brief    웹브라우저를 구분하기 위해 발급되는 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the ID issued to distinguish the web browser.
                * \endenglish
                * @return   const wchar_t* uuid
                */
                const wchar_t* GetUUID() const;

                /*!
                * \korean
                * @brief    레퍼런스(런처 또는 SGA)의 최초 구동 프로토콜을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the initial operation protocol of the reference (launcher or SGA).
                * \endenglish
                * @return   const wchar_t* serviceProtocol
                */
                const wchar_t* GetServiceProtocol() const;

                /*!
                * \korean
                * @brief    레퍼런스(런처 또는 SGA)의 원천 유형을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the source type of the reference (launcher or SGA).
                * \endenglish
                * @return   const wchar_t* refSourceType
                */
                const wchar_t* GetRefSourceType() const;

            public:
                StovePCTraceHint();
                StovePCTraceHint(const StovePCTraceHint& rhs);
                StovePCTraceHint(const StovePCTraceHintCpp* rhs);
                ~StovePCTraceHint();

                StovePCTraceHint& operator=(const StovePCTraceHint& rhs);
                StovePCTraceHint& operator=(const StovePCTraceHintCpp* rhs);

            private:
                void DeepCopy(const StovePCTraceHint& rhs);
                void DeepCopy(const StovePCTraceHintCpp* rhs);

                /*!
                * \korean
                * @brief    PCSDK가 초기화 될 때마다 발급되는 세션 아이디
                * \endkorean
                * \english
                * @brief    Session ID issued each time the PCSDK is initialized
                * \endenglish
                */
                wchar_t* sessionId = nullptr;

                /*!
                * \korean
                * @brief    레퍼런스(런처 또는 SGA)가 실행될 때마다 발급되는 세션 아이디
                * \endkorean
                * \english
                * @brief    Session ID issued each time the reference (launcher or SGA) is executed
                * \endenglish
                */
                wchar_t* refSessionId = nullptr;

                /*!
                * \korean
                * @brief    웹브라우저를 구분하기 위해 발급되는 아이디
                * \endkorean
                * \english
                * @brief    ID issued to distinguish the web browser
                * \endenglish
                */
                wchar_t* uuid = nullptr;

                /*!
                * \korean
                * @brief    레퍼런스(런처 또는 SGA)의 최초 구동 프로토콜
                * \endkorean
                * \english
                * @brief    Initial operation protocol of the reference (launcher or SGA)
                * \endenglish
                */
                wchar_t* serviceProtocol = nullptr;

                /*!
                * \korean
                * @brief    레퍼런스(런처 또는 SGA)의 원천 유형
                * \endkorean
                * \english
                * @brief    Source type of the reference (launcher or SGA)
                * \endenglish
                */
                wchar_t* refSourceType = nullptr;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCGameProfile
            * \korean
            * @brief Base_SetGameProfile API 호출시 전달하는 GameProfile 구조체입니다.
            * \endkorean
            * \english
            * @brief GameProfile structure passed when calling the Base_SetGameProfile API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCGameProfile
            {
            public:
                /*!
                * \korean
                * @brief    게임의 월드 식별자를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the world identifier of the game.
                * \endenglish
                * @return   const wchar_t* worldId
                */
                const wchar_t* GetWorldId() const;

                /*!
                * \korean
                * @brief    게임의 월드 식별자를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the world identifier of the game.
                * \endenglish
                * @param    const wchar_t* worldId
                */
                void SetWorldId(const wchar_t* worldId);

                /*!
                * \korean
                * @brief    캐릭터 식별자를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the character identifier.
                * \endenglish
                * @return   int64_t characterNumber
                */
                int64_t GetCharacterNumber() const;

                /*!
                * \korean
                * @brief    캐릭터 식별자를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the character identifier.
                * \endenglish
                * @param    int64_t number
                */
                void SetCharacterNumber(int64_t number);

            public:
                StovePCGameProfile();
                StovePCGameProfile(const wchar_t* worldId, int64_t characterNumber);
                StovePCGameProfile(const StovePCGameProfile& rhs);
                StovePCGameProfile(const StovePCGameProfileCpp* rhs);
                ~StovePCGameProfile();

                StovePCGameProfile& operator=(const StovePCGameProfile& rhs);
                StovePCGameProfile& operator=(const StovePCGameProfileCpp* rhs);

            private:
                void DeepCopy(const StovePCGameProfile& rhs);
                void DeepCopy(const StovePCGameProfileCpp* rhs);

                /*!
                * \korean
                * @brief    게임의 월드 식별자
                * \endkorean
                * \english
                * @brief    World identifier of the game
                * \endenglish
                */
                wchar_t* worldId = nullptr;

                /*!
                * \korean
                * @brief    캐릭터 식별자
                * \endkorean
                * \english
                * @brief    Character identifier
                * \endenglish
                */
                int64_t characterNumber;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCVietnamAgeRatingInfo
            * \korean
            * @brief Base_VietnamAgeRatingNotification API 호출시 전달받는 베트남 연령 등급 안내에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure for Vietnam age rating info received when calling the Base_VietnamAgeRatingNotification API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCVietnamAgeRatingInfo
            {
            public:
                /*!
                * \korean
                * @brief    오버레이 표시 상태를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the overlay display state.
                * \endenglish
                * @return   StoveOverlayState overlayState
                */
                StoveOverlayState GetOverlayState() const;

                /*!
                * \korean
                * @brief    오버레이 타입을 가져옵니다.
                * @details  0=검은색, 1=흰색
                * \endkorean
                * \english
                * @brief    Get the overlay type.
                * @details  0=black, 1=white
                * \endenglish
                * @return   int overlayType
                */
                int GetOverlayType() const;

                /*!
                * \korean
                * @brief    오버레이 크기를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the overlay scale.
                * \endenglish
                * @return   float overlayScale (0.0 ~ 1.0)
                */
                float GetOverlayScale() const;

                /*!
                * \korean
                * @brief    오버레이 불투명도를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the overlay opacity.
                * \endenglish
                * @return   float overlayOpacity (0.0 ~ 1.0)
                */
                float GetOverlayOpacity() const;

                /*!
                * \korean
                * @brief    게임 이용 등급을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game age rating.
                * \endenglish
                * @return   int ageRating (0=전체이용가, 12=12세, 16=16세, 18=18세)
                */
                int GetAgeRating() const;

                /*!
                * \korean
                * @brief    연령 등급 안내 메세지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the age rating notification message.
                * \endenglish
                * @return   const wchar_t* message
                */
                const wchar_t* GetAgeRatingMessage() const;

                /*!
                * \korean
                * @brief    메세지 노출 위치(x좌표)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the message display position (x-coordinate).
                * \endenglish
                * @return   float displayPositionX
                */
                float GetDisplayPositionX() const;

                /*!
                * \korean
                * @brief    메세지 노출 위치(y좌표)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the message display position (y-coordinate).
                * \endenglish
                * @return   float displayPositionY
                */
                float GetDisplayPositionY() const;

                /*!
                * \korean
                * @brief    언어 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the language code.
                * \endenglish
                * @return   const wchar_t* language (예: "ko", "en", "ja", "vi", "zh-cn", "zh-tw", "th")
                */
                const wchar_t* GetLanguage() const;

            public:
                StovePCVietnamAgeRatingInfo();
                StovePCVietnamAgeRatingInfo(const StovePCVietnamAgeRatingInfo& rhs);
                StovePCVietnamAgeRatingInfo(const StovePCVietnamAgeRatingInfoCpp* rhs);
                ~StovePCVietnamAgeRatingInfo();

                StovePCVietnamAgeRatingInfo& operator=(const StovePCVietnamAgeRatingInfo& rhs);
                StovePCVietnamAgeRatingInfo& operator=(const StovePCVietnamAgeRatingInfoCpp* rhs);

            private:
                void DeepCopy(const StovePCVietnamAgeRatingInfo& rhs);
                void DeepCopy(const StovePCVietnamAgeRatingInfoCpp* rhs);

                StoveOverlayState overlayState;
                int overlayType = 0;
                float overlayScale = 1.0f;
                float overlayOpacity = 1.0f;
                int ageRating = 18;
                wchar_t* message = nullptr;
                float displayPositionX;
                float displayPositionY;
                wchar_t* language = nullptr;

                /// Reserved fields for future extension
                uint64_t reserved1;
                uint64_t reserved2;
                uint64_t reserved3;
                uint64_t reserved4;
                uint64_t reserved5;
                uint64_t reserved6;
                uint64_t reserved7;
                uint64_t reserved8;
                uint64_t reserved9;
                uint64_t reserved10;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCVietnamOverimmersionInfo
            * \korean
            * @brief Base_VietnamOverimmersionNotification API 호출시 전달받는 베트남 과몰입 정보에 대한 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure for Vietnam overimmersion info received when calling the Base_VietnamOverimmersionNotification API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCVietnamOverimmersionInfo
            {
            public:
                /*!
                * \korean
                * @brief    오버레이 표시 상태를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the overlay display state.
                * \endenglish
                * @return   StoveOverlayState overlayState
                */
                StoveOverlayState GetOverlayState() const;

                /*!
                * \korean
                * @brief    오버레이 타입을 가져옵니다.
                * @details  0=검은색, 1=흰색
                * \endkorean
                * \english
                * @brief    Get the overlay type.
                * @details  0=black, 1=white
                * \endenglish
                * @return   int overlayType
                */
                int GetOverlayType() const;

                /*!
                * \korean
                * @brief    오버레이 크기를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the overlay scale.
                * \endenglish
                * @return   float overlayScale (0.0 ~ 1.0)
                */
                float GetOverlayScale() const;

                /*!
                * \korean
                * @brief    오버레이 불투명도를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the overlay opacity.
                * \endenglish
                * @return   float overlayOpacity (0.0 ~ 1.0)
                */
                float GetOverlayOpacity() const;

                /*!
                * \korean
                * @brief    게임 이용 등급을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game age rating.
                * \endenglish
                * @return   int ageRating (0=전체이용가, 12=12세, 16=16세, 18=18세)
                */
                int GetAgeRating() const;

                /*!
                * \korean
                * @brief    과몰입 경고 메세지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the over-immersion warning message.
                * \endenglish
                * @return   const wchar_t* message
                */
                const wchar_t* GetOverimmersionMessage() const;

                /*!
                * \korean
                * @brief    마크업 태그가 포함된 디자인용 메세지를 가져옵니다.
                * @details  <b>, <color=#RRGGBBAA> 등의 마크업 태그를 포함한 과몰입 경고 메세지입니다.
                * \endkorean
                * \english
                * @brief    Get the styled message with markup tags.
                * @details  Over-immersion warning message including markup tags such as <b>, <color=#RRGGBBAA>.
                * \endenglish
                * @return   const wchar_t* styledMessage
                */
                const wchar_t* GetStyledMessage() const;

                /*!
                * \korean
                * @brief    게임 경과시간(분)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game elapsed time (minute).
                * \endenglish
                * @return   int32_t elapsedTime
                */
                int32_t GetElapsedTime() const;

                /*!
                * \korean
                * @brief    메세지 노출 시간(초)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the message exposure time (seconds).
                * \endenglish
                * @return   int32_t exposureTime
                */
                int32_t GetExposureTime() const;

                /*!
                * \korean
                * @brief    Expand 애니메이션 시간(초)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the expand animation time (seconds).
                * \endenglish
                * @return   float expandAnimationTime
                */
                float GetExpandAnimationTime() const;

                /*!
                * \korean
                * @brief    메세지 노출 위치(x좌표)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the message display position (x-coordinate).
                * \endenglish
                * @return   float displayPositionX
                */
                float GetDisplayPositionX() const;

                /*!
                * \korean
                * @brief    메세지 노출 위치(y좌표)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the message display position (y-coordinate).
                * \endenglish
                * @return   float displayPositionY
                */
                float GetDisplayPositionY() const;

                /*!
                * \korean
                * @brief    언어 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the language code.
                * \endenglish
                * @return   const wchar_t* language (예: "ko", "en", "ja", "vi", "zh-cn", "zh-tw", "th")
                */
                const wchar_t* GetLanguage() const;

            public:
                StovePCVietnamOverimmersionInfo();
                StovePCVietnamOverimmersionInfo(const StovePCVietnamOverimmersionInfo& rhs);
                StovePCVietnamOverimmersionInfo(const StovePCVietnamOverimmersionInfoCpp* rhs);
                ~StovePCVietnamOverimmersionInfo();

                StovePCVietnamOverimmersionInfo& operator=(const StovePCVietnamOverimmersionInfo& rhs);
                StovePCVietnamOverimmersionInfo& operator=(const StovePCVietnamOverimmersionInfoCpp* rhs);

            private:
                void DeepCopy(const StovePCVietnamOverimmersionInfo& rhs);
                void DeepCopy(const StovePCVietnamOverimmersionInfoCpp* rhs);

                StoveOverlayState overlayState;
                int overlayType = 0;
                float overlayScale = 1.0f;
                float overlayOpacity = 1.0f;
                int ageRating = 18;
                wchar_t* message = nullptr;
                wchar_t* styledMessage = nullptr;
                int32_t elapsedTime;
                int32_t exposureTime;
                float expandAnimationTime = 0.3f;
                float displayPositionX;
                float displayPositionY;
                wchar_t* language = nullptr;

                /// Reserved fields for future extension
                uint64_t reserved1;
                uint64_t reserved2;
                uint64_t reserved3;
                uint64_t reserved4;
                uint64_t reserved5;
                uint64_t reserved6;
                uint64_t reserved7;
                uint64_t reserved8;
                uint64_t reserved9;
                uint64_t reserved10;
            };
#pragma pack(pop)
        }
    }
}

