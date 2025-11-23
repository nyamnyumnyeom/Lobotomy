#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LB_SubtitleData.generated.h"

USTRUCT(BlueprintType)
struct FLB_SubtitleData : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EndTime = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Subtitle;
};