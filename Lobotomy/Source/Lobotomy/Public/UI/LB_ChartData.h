#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LB_ChartData.generated.h"

USTRUCT(BlueprintType)
struct FChartData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Symptom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Remark;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PageNumber = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<bool> DayChecks;
};
