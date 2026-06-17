#pragma once

/*!
    * @file     Structures.h
    * \korean
    * @brief    GameSupportSDK에서 사용하는 Structures 값의 헤더 파일입니다.
    * \endkorean
    * \english
    * @brief    Header file of Structures values used in GameSupportSDK.
    * \endenglish
*/

#include <string>

#include "Misc/SDKExports.h"

namespace Stove
{
    namespace PCSDK
    {
        namespace GameSupport
        {
            struct StovePCStatFullIdCpp;
            struct StovePCStatCpp;
            struct StovePCModifyStatValueCpp;
            struct StovePCAchievementConditionCpp;
            struct StovePCAchievementCpp;
            struct StovePCRankParamsCpp;
            struct StovePCRankCpp;

            /*!
            * @struct StovePCStatFullId
            * \korean
            * @brief GameSupportSDK_Stat API 호출시 응답받는 콜백의 StatFullId 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of StatFullId received when calling the GameSupportSDK_Stat API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCStatFullId
            {
            public:
                /*!
                * \korean
                * @brief    Stats 게임 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stats game ID.
                * \endenglish
                * @return   const wchar_t* gameId
                */
                const wchar_t* GetGameId() const;

                /*!
                * \korean
                * @brief    Stat 아이디 [A-Z0-9\\-_]*$ 형식(영문 대문자, 숫자, underscore, hyphen)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Stat ID [A-Z0-9\\-_]*$ format (uppercase letters, numbers, underscore, hyphen).
                * \endenglish
                * @return   const wchar_t* statId
                */
                const wchar_t* GetStatId() const;

            public:
                StovePCStatFullId();
                StovePCStatFullId(const StovePCStatFullId& rhs);
                StovePCStatFullId(const StovePCStatFullIdCpp* rhs);
                ~StovePCStatFullId();

                StovePCStatFullId& operator=(const StovePCStatFullId& rhs);
                StovePCStatFullId& operator=(const StovePCStatFullIdCpp* rhs);

            private:
                void DeepCopy(const StovePCStatFullId& rhs);
                void DeepCopy(const StovePCStatFullIdCpp* rhs);

                /*!
                * \korean
                * @brief    Stats 게임 아이디
                * \endkorean
                * \english
                * @brief    Stats game ID
                * \endenglish
                */
                wchar_t* gameId = nullptr;

                /*!
                * \korean
                * @brief    Stat 아이디 [A-Z0-9\\-_]*$ 형식(영문 대문자, 숫자, underscore, hyphen)
                * \endkorean
                * \english
                * @brief    Stat ID [A-Z0-9\\-_]*$ format (uppercase letters, numbers, underscore, hyphen)
                * \endenglish
                */
                wchar_t* statId = nullptr;
            };
#pragma pack(pop)


            /*!
            * @struct StovePCStat
            * \korean
            * @brief GameSupportSDK_Stat API 호출시 응답받는 콜백의 Stat 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of Stat received when calling the GameSupportSDK_Stat API.
            * \endenlgish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCStat
            {
            public:
                /*!
                * \korean
                * @brief    Stat 전체 ID를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the full ID of the Stat.
                * \endenglish
                * @return   const StovePCStatFullId* statFullId
                */
                const StovePCStatFullId* GetStatFullId() const;

                /*!
                * \korean
                * @brief    Stat 최종 업데이트 시간(epoch time milliseconds)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the last update time of the Stat (epoch time milliseconds).
                * \endenglish
                * @return   uint64_t updatedAt
                */
                uint64_t GetUpdatedAt() const;

                /*!
                * \korean
                * @brief    Stat 현재 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the current value of the Stat.
                * \endenglish
                * @return   int32_t currentValue
                */
                int32_t GetCurrentValue() const;

            public:
                StovePCStat();
                StovePCStat(const StovePCStat& rhs);
                StovePCStat(const StovePCStatCpp* rhs);
                ~StovePCStat() = default;

                StovePCStat& operator=(const StovePCStat& rhs);
                StovePCStat& operator=(const StovePCStatCpp* rhs);

            private:
                void DeepCopy(const StovePCStat& rhs);
                void DeepCopy(const StovePCStatCpp* rhs);

                /*!
                * \korean
                * @brief    Stat 전체 ID
                * \endkorean
                * \english
                * @brief    Full ID of the Stat
                * \endenglish
                */
                StovePCStatFullId statFullId;

                /*!
                * \korean
                * @brief    Stat 최종 업데이트 시간(epoch time milliseconds)
                * \endkorean
                * \english
                * @brief    Last update time of the Stat (epoch time milliseconds)
                * \endenglish
                */
                uint64_t updatedAt;

                /*!
                * \korean
                * @brief    Stat 현재 값
                * \endkorean
                * \english
                * @brief    Current value of the Stat
                * \endenglish
                */
                int32_t currentValue;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCModifyStatValue
            * \korean
            * @brief GameSupport_ModifyStat API 호출시 응답받는 콜백의 StatValue 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of StatValue received when calling the GameSupport_ModifyStat API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCModifyStatValue
            {
            public:
                /*!
                * \korean
                * @brief    오류 메시지를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the error message.
                * \endenglish
                * @return   const wchar_t* errorMessage
                */
                const wchar_t* GetErrorMessage() const;

                /*!
                * \korean
                * @brief    Stat 현재 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the current value of the Stat.
                * \endenglish
                * @return   int32_t currentValue
                */
                int32_t GetCurrentValue() const;

                /*!
                * \korean
                * @brief    Stat 값의 변경 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get whether the value of the Stat has changed.
                * \endenglish
                * @return   bool updated
                */
                bool IsUpdated() const;

            public:
                StovePCModifyStatValue();
                StovePCModifyStatValue(const StovePCModifyStatValue& rhs);
                StovePCModifyStatValue(const StovePCModifyStatValueCpp* rhs);
                ~StovePCModifyStatValue();

                StovePCModifyStatValue& operator=(const StovePCModifyStatValue& rhs);
                StovePCModifyStatValue& operator=(const StovePCModifyStatValueCpp* rhs);

            private:
                void DeepCopy(const StovePCModifyStatValue& rhs);
                void DeepCopy(const StovePCModifyStatValueCpp* rhs);

                /*!
                * \korean
                * @brief    오류 메시지
                * \endkorean
                * \english
                * @brief    Error message
                * \endenglish
                */
                wchar_t* errorMessage = nullptr;

                /*!
                * \korean
                * @brief    Stat 현재 값
                * \endkorean
                * \english
                * @brief    Current value of the Stat
                * \endenglish
                */
                int32_t currentValue;

                /*!
                * \korean
                * @brief    Stat 값의 변경 여부
                * \endkorean
                * \english
                * @brief    Whether the value of the Stat has changed
                * \endenglish
                */
                bool updated;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCAchievementCondition
            * \korean
            * @brief GameSupportSDK_Achievement 및 GameSupportSDK_AllAchievement API 호출시 응답받는 콜백의 AchievementCondition 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of AchievementCondition received when calling the GameSupportSDK_Achievement and GameSupportSDK_AllAchievement APIs.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCAchievementCondition
            {
            public:
                /*!
                * \korean
                * @brief    값 처리 방법 (DELTA_SUM: 누적 데이터 합계, REPLACE: 기존 데이터 교체, MAX : 큰값으로 대체, MIN : 작은값으로 대체)을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the value processing method (DELTA_SUM: cumulative data sum, REPLACE: replace existing data, MAX: replace with larger value, MIN: replace with smaller value).
                * \endenglish
                * @return   const wchar_t* valueOperation
                */
                const wchar_t* GetValueOperation() const;

                /*!
                * \korean
                * @brief    Achievement 목표값과 사용자 업적 값의 비교 연산 방식 ( GTE: >=, LTE: <= )을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the comparison operation method between the Achievement goal value and the user achievement value (GTE: >=, LTE: <=).
                * \endenglish
                * @return   const wchar_t* type
                */
                const wchar_t* GetType() const;

                /*!
                * \korean
                * @brief    Achievement 달성 목표 값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Achievement goal value.
                * \endenglish
                * @return   int32_t goalValue
                */
                int32_t GetGoalValue() const;

            public:
                StovePCAchievementCondition();
                StovePCAchievementCondition(const StovePCAchievementCondition& rhs);
                StovePCAchievementCondition(const StovePCAchievementConditionCpp* rhs);
                ~StovePCAchievementCondition();

                StovePCAchievementCondition& operator=(const StovePCAchievementCondition& rhs);
                StovePCAchievementCondition& operator=(const StovePCAchievementConditionCpp* rhs);

            private:
                void DeepCopy(const StovePCAchievementCondition& rhs);
                void DeepCopy(const StovePCAchievementConditionCpp* rhs);

                /*!
                * \korean
                * @brief    값 처리 방법 (DELTA_SUM: 누적 데이터 합계, REPLACE: 기존 데이터 교체, MAX : 큰값으로 대체, MIN : 작은값으로 대체)
                * \endkorean
                * \english
                * @brief    Value processing method (DELTA_SUM: cumulative data sum, REPLACE: replace existing data, MAX: replace with larger value, MIN: replace with smaller value)
                * \endenglish
                */
                wchar_t* valueOperation = nullptr;

                /*!
                * \korean
                * @brief    Achievement 목표값과 사용자 업적 값의 비교 연산 방식 ( GTE: >=, LTE: <= )
                * \endkorean
                * \english
                * @brief    Comparison operation method between the Achievement goal value and the user achievement value (GTE: >=, LTE: <=)
                * \endenglish
                */
                wchar_t* type = nullptr;

                /*!
                * \korean
                * @brief    Achievement 달성 목표 값
                * \endkorean
                * \english
                * @brief    Achievement goal value
                * \endenglish
                */
                int32_t goalValue;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCAchievement
            * \korean
            * @brief GameSupportSDK_Achievement 및 GameSupportSDK_AllAchievement API 호출시 응답받는 콜백의 Achievement 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of Achievement received when calling the GameSupportSDK_Achievement and GameSupportSDK_AllAchievement APIs.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCAchievement
            {
            public:
                /*!
                * \korean
                * @brief    Achievement 조건을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Achievement condition.
                * \endenglish
                * @return   const StovePCAchievementCondition* condition
                */
                const StovePCAchievementCondition* GetCondition() const;

                /*!
                * \korean
                * @brief    Achievement 현재값을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the current value of the Achievement.
                * \endenglish
                * @return   int32_t value
                */
                int32_t GetValue() const;

                /*!
                * \korean
                * @brief    Achievement 아이디를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Achievement ID.
                * \endenglish
                * @return   const wchar_t* achievementId
                */
                const wchar_t* GetAchievementId() const;

                /*!
                * \korean
                * @brief    Achievement 이름을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Achievement name.
                * \endenglish
                * @return   const wchar_t* name
                */
                const wchar_t* GetName() const;

                /*!
                * \korean
                * @brief    Achievement 설명을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Achievement description.
                * \endenglish
                * @return   const wchar_t* description
                */
                const wchar_t* GetDescription() const;

                /*!
                * \korean
                * @brief    기본 이미지 URL을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the default image URL.
                * \endenglish
                * @return   const wchar_t* defaultImageUrl
                */
                const wchar_t* GetDefaultImageUrl() const;

                /*!
                * \korean
                * @brief    달성 이미지 URL을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the achieved image URL.
                * \endenglish
                * @return   const wchar_t* achievedImageUrl
                */
                const wchar_t* GetAchievedImageUrl() const;

                /*!
                * \korean
                * @brief    Achievement 상태 (ONGOING : 진행중, ACHIEVED: 업적 달성)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the Achievement status (ONGOING: in progress, ACHIEVED: achievement achieved).
                * \endenglish
                * @return   const wchar_t* status
                */
                const wchar_t* GetStatus() const;

            public:
                StovePCAchievement();
                StovePCAchievement(const StovePCAchievement& rhs);
                StovePCAchievement(const StovePCAchievementCpp* rhs);
                ~StovePCAchievement();

                StovePCAchievement& operator=(const StovePCAchievement& rhs);
                StovePCAchievement& operator=(const StovePCAchievementCpp* rhs);

            private:
                void DeepCopy(const StovePCAchievement& rhs);
                void DeepCopy(const StovePCAchievementCpp* rhs);

                /*!
                * \korean
                * @brief    Achievement 조건
                * \endkorean
                * \english
                * @brief    Achievement condition
                * \endenglish
                */
                StovePCAchievementCondition condition;

                /*!
                * \korean
                * @brief    Achievement 현재값
                * \endkorean
                * \english
                * @brief    Achievement current value
                * \endenglish
                */
                int32_t value;

                /*!
                * \korean
                * @brief    Achievement 아이디
                * \endkorean
                * \english
                * @brief    Achievement ID
                * \endenglish
                */
                wchar_t* achievementId = nullptr;

                /*!
                * \korean
                * @brief    Achievement 이름
                * \endkorean
                * \english
                * @brief    Achievement name
                * \endenglish
                */
                wchar_t* name = nullptr;

                /*!
                * \korean
                * @brief    Achievement 설명
                * \endkorean
                * \english
                * @brief    Achievement description
                * \endenglish
                */
                wchar_t* description = nullptr;

                /*!
                * \korean
                * @brief    기본 이미지 URL
                * \endkorean
                * \english
                * @brief    Default image URL
                * \endenglish
                */
                wchar_t* defaultImageUrl = nullptr;

                /*!
                * \korean
                * @brief    달성 이미지 URL
                * \endkorean
                * \english
                * @brief    Achieved image URL
                * \endenglish
                */
                wchar_t* achievedImageUrl = nullptr;

                /*!
                * \korean
                * @brief    Achievement 상태 (ONGOING : 진행중, ACHIEVED: 업적 달성)
                * \endkorean
                * \english
                * @brief    Achievement status (ONGOING: in progress, ACHIEVED: achievement achieved)
                * \endenglish
                */
                wchar_t* status = nullptr;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCRankParams
            * \korean
            * @brief GameSupportSDK_Rank API 호출시 전달할 매개변수들을 담는 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure containing parameters to be passed when calling the GameSupportSDK_Rank API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCRankParams
            {
            public:
                /*!
                * \korean
                * @brief    스튜디오에서 생성한 리더보드 식별자를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the leaderboard identifier created by the studio.
                * \endenglish
                * @return   const wchar_t* leaderboardId
                */
                const wchar_t* GetLeaderBoardId() const;

                /*!
                * \korean
                * @brief    스튜디오에서 생성한 리더보드 식별자를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the leaderboard identifier created by the studio.
                * \endenglish
                * @param    const wchar_t* leaderboardId
                */
                void SetLeaderBoardId(const wchar_t* leaderboardId);

                /*!
                * \korean
                * @brief    조회할 페이지 번호 (1 <= pageIndex)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the page number to be viewed (1 <= pageIndex).
                * \endenglish
                * @return   uint32_t pageIndex
                */
                uint32_t GetPageIndex() const;

                /*!
                * \korean
                * @brief    조회할 페이지 번호 (1 <= pageIndex)를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the page number to be viewed (1 <= pageIndex).
                * \endenglish
                * @param    uint32_t pageIndex
                */
                void SetPageIndex(uint32_t pageIndex);

                /*!
                * \korean
                * @brief    조회할 순위의 개수 (1 <= pageSize <= 50)를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the number of rankings to be viewed (1 <= pageSize <= 50).
                * \endenglish
                * @return   uint32_t pageSize
                */
                uint32_t GetPageSize() const;

                /*!
                * \korean
                * @brief    조회할 순위의 개수 (1 <= pageSize <= 50)를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set the number of rankings to be viewed (1 <= pageSize <= 50).
                * \endenglish
                * @return   uint32_t pageSize
                */
                void SetPageSize(uint32_t pageSize);

                /*!
                * \korean
                * @brief    조회결과에 로그인한 사용자의 순위를 포함할지 여부를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get whether to include the rank of the logged-in user in the search results.
                * \endenglish
                * @return   bool includeMyRank
                */
                bool IsIncludeMyRank() const;

                /*!
                * \korean
                * @brief    조회결과에 로그인한 사용자의 순위를 포함할지 여부를 설정합니다.
                * \endkorean
                * \english
                * @brief    Set whether to include the rank of the logged-in user in the search results.
                * \endenglish
                * @return   bool includeMyRank
                */
                void SetIncludeMyRank(bool includeMyRank);

            public:
                StovePCRankParams();
                StovePCRankParams(const wchar_t* leaderboardId, uint32_t pageIndex, uint32_t pageSize, bool includeMyRank);
                StovePCRankParams(const StovePCRankParams& rhs);
                StovePCRankParams(const StovePCRankParamsCpp* rhs);
                ~StovePCRankParams();

                StovePCRankParams& operator=(const StovePCRankParams& rhs);
                StovePCRankParams& operator=(const StovePCRankParamsCpp* rhs);

            private:
                void DeepCopy(const StovePCRankParams& rhs);
                void DeepCopy(const StovePCRankParamsCpp* rhs);

                /*!
                * \korean
                * @brief    스튜디오에서 생성한 리더보드 식별자
                * \endkorean
                * \english
                * @brief    Leaderboard identifier created by the studio
                * \endenglish
                */
                wchar_t* leaderboardId = nullptr;

                /*!
                * \korean
                * @brief    조회할 페이지 번호 (1 <= pageIndex)
                * \endkorean
                * \english
                * @brief    Page number to be viewed (1 <= pageIndex)
                * \endenglish
                */
                uint32_t pageIndex;

                /*!
                * \korean
                * @brief    조회할 순위의 개수 (1 <= pageSize <= 50)
                * \endkorean
                * \english
                * @brief    Number of rankings to be viewed (1 <= pageSize <= 50)
                * \endenglish
                */
                uint32_t pageSize;

                /*!
                * \korean
                * @brief    조회결과에 로그인한 사용자의 순위를 포함할지 여부
                * \endkorean
                * \english
                * @brief    Whether to include the rank of the logged-in user in the search results
                * \endenglish
                */
                bool includeMyRank;
            };
#pragma pack(pop)

            /*!
            * @struct StovePCRank
            * \korean
            * @brief GameSupportSDK_Rank API 호출시 응답받는 콜백의 Rank 구조체입니다.
            * \endkorean
            * \english
            * @brief Structure of Rank received when calling the GameSupportSDK_Rank API.
            * \endenglish
            */
#pragma pack(push, 4)
            struct SDK_EXPORTS StovePCRank
            {
            public:
                /*!
                * \korean
                * @brief    닉네임을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the nickname.
                * \endenglish
                * @return   const wchar_t* nickname
                */
                const wchar_t* GetNickname() const;

                /*!
                * \korean
                * @brief    프로필 이미지 URL을 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the profile image URL.
                * \endenglish
                * @return   const wchar_t* profileImage
                */
                const wchar_t* GetProfileImage() const;

                /*!
                * \korean
                * @brief    점수를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the score.
                * \endenglish
                * @return   int32_t score
                */
                int32_t GetScore() const;

                /*!
                * \korean
                * @brief    순위를 가져옵니다.
                * \endkorean
                * \english
                * @brief    Get the rank.
                * \endenglish
                * @return   uint32_t rank
                */
                uint32_t GetRank() const;

            public:
                StovePCRank();
                StovePCRank(const StovePCRank& rhs);
                StovePCRank(const StovePCRankCpp* rhs);
                ~StovePCRank();

                StovePCRank& operator=(const StovePCRank& rhs);
                StovePCRank& operator=(const StovePCRankCpp* rhs);

            private:
                void DeepCopy(const StovePCRank& rhs);
                void DeepCopy(const StovePCRankCpp* rhs);

                /*!
                * \korean
                * @brief    닉네임
                * \endkorean
                * \english
                * @brief    Nickname
                * \endenglish
                */
                wchar_t* nickname = nullptr;

                /*!
                * \korean
                * @brief    프로필 이미지 URL
                * \endkorean
                * \english
                * @brief    Profile image URL
                * \endenglish
                */
                wchar_t* profileImage = nullptr;

                /*!
                * \korean
                * @brief    점수
                * \endkorean
                * \english
                * @brief    Score
                * \endenglish
                */
                int32_t score;

                /*!
                * \korean
                * @brief    순위
                * \endkorean
                * \english
                * @brief    Rank
                * \endenglish
                */
                uint32_t rank;
            };
#pragma pack(pop)
        }
    }
}
