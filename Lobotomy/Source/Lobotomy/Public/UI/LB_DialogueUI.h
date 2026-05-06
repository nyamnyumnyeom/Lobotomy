// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LB_DialogueData.h"
#include "LB_DialogueUI.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEventTriggered);

UCLASS()
class LOBOTOMY_API ULB_DialogueUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void InitDialogue(UDataTable* InTable, FName StartRow);

    UFUNCTION(BlueprintCallable)
    void ShowNextDialogue();

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueEventTriggered OnDialogueEventTriggered;

protected:
    void DisplayCurrentDialogue();

    UPROPERTY()
    UDataTable* DialogueTable;

    UPROPERTY()
    FDialogueRow CurrentRow;

    UPROPERTY()
    FName CurrentRowName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SpeakerText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DialogueText;

    UPROPERTY(meta = (BindWidgetOptional))
    UButton* NextButton;
};
