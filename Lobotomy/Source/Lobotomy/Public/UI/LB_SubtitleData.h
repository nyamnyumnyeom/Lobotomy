#pragma once

#include "CoreMinimal.h"
#include "LB_SubtitleData.generated.h"

USTRUCT(BlueprintType)
struct FLB_SubtitleData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EndTime = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Text;
};