#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "Engine/DataTable.h"
#include "LB_DialogueData.generated.h"


USTRUCT(BlueprintType)
struct FDialogueRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName DialogueID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FText SpeakerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FText DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName NextID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TObjectPtr<USoundBase> DialogueSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    bool bPlaySound = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    bool bUseInventoryBranch = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName EmptyInventoryNextID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName OccupiedInventoryNextID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName RewardItemID = NAME_None;
};