#pragma once

/*!
    * @file     Structures.h
    * \korean
    * @brief    LogSDK에서 사용하는 Structures 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Structures values used in LogSDK.
    * \endenglish
*/

#include <string>

#include "Misc/BaseSDKStructures.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace Log
        {
            struct StovePCLogSendParamCpp;

            /*!
            * @struct StovePCLogSendParam
            * \korean
            * @brief Log_Send API를 호출할 때 전달하는 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure to be passed when calling the Log_Send API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCLogSendParam
            {
            public:
                /*!
                * \korean
                * @brief    AUID를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the AUID.
                * \endenglish
                * @return   int64_t auid
                */
                int64_t GetAuid() const;

                /*!
                * \korean
                * @brief    AUID를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the AUID.
                * \endenglish
                * @param    int64_t auid
                */
                void SetAuid(int64_t auid);

                /*!
                * \korean
                * @brief    CUID를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the CUID.
                * \endenglish
                * @return   int64_t cuid
                */
                int64_t GetCuid() const;

                /*!
                * \korean
                * @brief    CUID를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the CUID.
                * \endenglish
                * @param    int64_t cuid
                */
                void SetCuid(int64_t cuid);

                /*!
                * \korean
                * @brief    마케팅 타입 1을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the marketing type 1.
                * \endenglish
                * @return   const wchar_t* mktType1
                */
                const wchar_t* GetMktType1() const;

                /*!
                * \korean
                * @brief    마케팅 타입 1을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the marketing type 1.
                * \endenglish
                * @param    const wchar_t* mktType1
                */
                void SetMktType1(const wchar_t* mktType1);

                /*!
                * \korean
                * @brief    마케팅 아이디 1을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the marketing ID 1.
                * \endenglish
                * @return   const wchar_t* mktId1
                */
                const wchar_t* GetMktId1() const;

                /*!
                * \korean
                * @brief    마케팅 아이디 1을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the marketing ID 1.
                * \endenglish
                * @param    const wchar_t* mktId1
                */
                void SetMktId1(const wchar_t* mktId1);

                /*!
                * \korean
                * @brief    마케팅 타입 2를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the marketing type 2.
                * \endenglish
                * @return   const wchar_t* mktType2
                */
                const wchar_t* GetMktType2() const;

                /*!
                * \korean
                * @brief    마케팅 타입 2를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the marketing type 2.
                * \endenglish
                * @param    const wchar_t* mktType2
                */
                void SetMktType2(const wchar_t* mktType2);

                /*!
                * \korean
                * @brief    마케팅 아이디 2를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the marketing ID 2.
                * \endenglish
                * @return   const wchar_t* mktId2
                */
                const wchar_t* GetMktId2() const;

                /*!
                * \korean
                * @brief    마케팅 아이디 2를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the marketing ID 2.
                * \endenglish
                * @param    const wchar_t* mktId2
                */
                void SetMktId2(const wchar_t* mktId2);

                /*!
                * \korean
                * @brief    게임 버전을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the game version.
                * \endenglish
                * @return   const wchar_t* gameVersion
                */
                const wchar_t* GetGameVersion() const;

                /*!
                * \korean
                * @brief    게임 버전을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the game version.
                * \endenglish
                * @param    const wchar_t* gameVersion
                */
                void SetGameVersion(const wchar_t* gameVersion);

                /*!
                * \korean
                * @brief    로그 그룹 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the log group ID.
                * \endenglish
                * @return   const wchar_t* logGroupId
                */
                const wchar_t* GetLogGroupId() const;

                /*!
                * \korean
                * @brief    로그 그룹 아이디를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the log group ID.
                * \endenglish
                * @param    const wchar_t* logGroupId
                */
                void SetLogGroupId(const wchar_t* logGroupId);

                /*!
                * \korean
                * @brief    서버 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the server code.
                * \endenglish
                * @return   const wchar_t* serverCd
                */
                const wchar_t* GetServerCd() const;

                /*!
                * \korean
                * @brief    서버 코드를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the server code.
                * \endenglish
                * @param    const wchar_t* serverCd
                */
                void SetServerCd(const wchar_t* serverCd);

                /*!
                * \korean
                * @brief    서버 코드 상세를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the server code detail.
                * \endenglish
                * @return   const wchar_t* serverCdDet
                */
                const wchar_t* GetServerCdDet() const;

                /*!
                * \korean
                * @brief    서버 코드 상세를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the server code detail.
                * \endenglish
                * @param    const wchar_t* serverCdDet
                */
                void SetServerCdDet(const wchar_t* serverCdDet);

                /*!
                * \korean
                * @brief    레벨 코드를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the level code.
                * \endenglish
                * @return   const wchar_t* lvCd
                */
                const wchar_t* GetLvCd() const;

                /*!
                * \korean
                * @brief    레벨 코드를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the level code.
                * \endenglish
                * @param    const wchar_t* lvCd
                */
                void SetLvCd(const wchar_t* lvCd);

                /*!
                * \korean
                * @brief    레벨 코드 상세를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the level code detail.
                * \endenglish
                * @return   const wchar_t* lvCdDet
                */
                const wchar_t* GetLvCdDet() const;

                /*!
                * \korean
                * @brief    레벨 코드 상세를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the level code detail.
                * \endenglish
                * @param    const wchar_t* lvCdDet
                */
                void SetLvCdDet(const wchar_t* lvCdDet);

                /*!
                * \korean
                * @brief    컨텐츠 JSON 문자열을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the contents JSON string.
                * \endenglish
                * @return   const wchar_t* contents
                */
                const wchar_t* GetContents() const;

                /*!
                * \korean
                * @brief    컨텐츠 JSON 문자열을 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the contents JSON string.
                * \endenglish
                * @param    const wchar_t* contents
                */
                void SetContents(const wchar_t* contents);

            public:
                StovePCLogSendParam();
                StovePCLogSendParam(const StovePCLogSendParam& rhs);
                StovePCLogSendParam(const StovePCLogSendParamCpp* rhs);
                ~StovePCLogSendParam();

                StovePCLogSendParam& operator=(const StovePCLogSendParam& rhs);
                StovePCLogSendParam& operator=(const StovePCLogSendParamCpp* rhs);

            private:
                void DeepCopy(const StovePCLogSendParam& rhs);
                void DeepCopy(const StovePCLogSendParamCpp* rhs);

            private:
                /*!
                * \korean
                * @brief    계정 단위의 고유 ID (게임에 해당 개념이 있을 경우)
                * \endkorean
                * \english
                * @brief    Unique ID per account (used when the game has this concept)
                * \endenglish
                */
                int64_t auid;

                /*!
                * \korean
                * @brief    캐릭터 단위의 고유 ID (게임에 해당 개념이 있을 경우)
                * \endkorean
                * \english
                * @brief    Unique ID per character (used when the game has this concept)
                * \endenglish
                */
                int64_t cuid;

                /*!
                * \korean
                * @brief    연동한 마케팅 3rd party 서비스 네임 (1)
                * \endkorean
                * \english
                * @brief    Integrated marketing 3rd party service name (1)
                * \endenglish
                */
                wchar_t* mktType1 = nullptr;

                /*!
                * \korean
                * @brief    연동한 마케팅 3rd party 서비스에 따른 고유 키 값 (1)
                * \endkorean
                * \english
                * @brief    Unique key value for integrated marketing 3rd party service (1)
                * \endenglish
                */
                wchar_t* mktId1 = nullptr;

                /*!
                * \korean
                * @brief    연동한 마케팅 3rd party 서비스 네임 (2)
                * \endkorean
                * \english
                * @brief    Integrated marketing 3rd party service name (2)
                * \endenglish
                */
                wchar_t* mktType2 = nullptr;

                /*!
                * \korean
                * @brief    연동한 마케팅 3rd party 서비스에 따른 고유 키 값 (2)
                * \endkorean
                * \english
                * @brief    Unique key value for integrated marketing 3rd party service (2)
                * \endenglish
                */
                wchar_t* mktId2 = nullptr;

                /*!
                * \korean
                * @brief    게임 빌드 버전
                * \endkorean
                * \english
                * @brief    Game build version
                * \endenglish
                */
                wchar_t* gameVersion = nullptr;

                /*!
                * \korean
                * @brief    세트로 묶여야 할 로그 간 매핑을 위한 Log Group ID
                * \endkorean
                * \english
                * @brief    Log Group ID for mapping between logs that should be grouped together
                * \endenglish
                */
                wchar_t* logGroupId = nullptr;

                /*!
                * \korean
                * @brief    서버 코드 (게임에 서버 개념이 있을 경우, 예: 라엘 / 로웨인 / 델리게온)
                * \endkorean
                * \english
                * @brief    Server code (used when the game has server concept, e.g., Raelle / Roween / Deligeon)
                * \endenglish
                */
                wchar_t* serverCd = nullptr;

                /*!
                * \korean
                * @brief    서버 코드 상세 정보 (게임에 서버 상세 정보가 있을 경우, 예: 01 / 02)
                * \endkorean
                * \english
                * @brief    Detailed server code information (used when the game has detailed server information, e.g., 01 / 02)
                * \endenglish
                */
                wchar_t* serverCdDet = nullptr;

                /*!
                * \korean
                * @brief    로그 기록 시점의 레벨 정보 (계정 단위)
                * \endkorean
                * \english
                * @brief    Level information at the time of log recording (account level)
                * \endenglish
                */
                wchar_t* lvCd = nullptr;

                /*!
                * \korean
                * @brief    로그 기록 시점의 레벨 정보 (캐릭터 단위)
                * \endkorean
                * \english
                * @brief    Level information at the time of log recording (character level)
                * \endenglish
                */
                wchar_t* lvCdDet = nullptr;

                /*!
                * \korean
                * @brief    위의 필드 이외의 데이터를 JSON 문자열로 전송
                * \endkorean
                * \english
                * @brief    Additional data other than the above fields sent as JSON string
                * \endenglish
                */
                wchar_t* contents = nullptr;
            };
#pragma pack(pop)
        }
    }
}
