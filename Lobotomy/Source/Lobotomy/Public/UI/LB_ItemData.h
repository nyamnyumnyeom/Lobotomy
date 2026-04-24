#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "LB_ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    None UMETA(DisplayName = "None"),
    Battery UMETA(DisplayName = "Battery"),
    Medicine UMETA(DisplayName = "Medicine"),
    Medicine2 UMETA(DisplayName = "Medicine2"),
    Key UMETA(DisplayName = "Key"),
    Tool UMETA(DisplayName = "Tool")
};

USTRUCT(BlueprintType)
struct FItemRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* ItemIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    EItemType ItemType = EItemType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftClassPtr<AActor> ItemClass;
};