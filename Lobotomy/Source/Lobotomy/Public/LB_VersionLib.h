#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LB_VersionLib.generated.h"

UCLASS()
class LOBOTOMY_API ULB_VersionLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Project")
    static FString GetProjectVersionString();
};
