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
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Symptom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Room;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Remark;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PageNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText RoomNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<bool> DayChecks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> NightChecks;
};
