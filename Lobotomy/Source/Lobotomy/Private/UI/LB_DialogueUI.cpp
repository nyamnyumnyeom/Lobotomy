#include "UI/LB_DialogueUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Character/LB_Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

void ULB_DialogueUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (NextButton)
    {
        NextButton->OnClicked.AddDynamic(this, &ULB_DialogueUI::ShowNextDialogue);
    }
}

void ULB_DialogueUI::InitDialogue(UDataTable* InTable, FName StartRow)
{
    DialogueTable = InTable;
    CurrentRowName = StartRow;
    DisplayCurrentDialogue();
}

void ULB_DialogueUI::ShowNextDialogue()
{
    if (!DialogueTable) return;

    FDialogueRow* NextRow = DialogueTable->FindRow<FDialogueRow>(CurrentRow.NextID, TEXT("ShowNextDialogue"));
    if (NextRow)
    {
        RemoveFromParent();
        MarkAsGarbage();

        if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
        {
            ULB_DialogueUI* NewUI = CreateWidget<ULB_DialogueUI>(PC, GetClass());
            if (NewUI)
            {
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(NewUI->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PC->SetInputMode(InputMode);

                NewUI->AddToViewport(1000);
                NewUI->InitDialogue(DialogueTable, NextRow->DialogueID);
            }
        }
    }
    else
    {
        RemoveFromParent();
        MarkAsGarbage();

        if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
        {
            FInputModeGameOnly GameInput;
            PC->SetInputMode(GameInput);
            PC->bShowMouseCursor = false;

            if (ALB_Character* Player = Cast<ALB_Character>(PC->GetPawn()))
            {
                Player->ShowHUDUI();
				Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
				Player->OnDialogueEnd();
            }
        }
    }
}

void ULB_DialogueUI::DisplayCurrentDialogue()
{
    if (!DialogueTable) return;

    FDialogueRow* Row = DialogueTable->FindRow<FDialogueRow>(CurrentRowName, TEXT("DisplayCurrentDialogue"));
    if (Row)
    {
        CurrentRow = *Row;
        if (SpeakerText)
        {
            SpeakerText->SetText(FText::GetEmpty());
        }
        if (DialogueText)
        {
            DialogueText->SetText(FText::GetEmpty());
        }

        if (SpeakerText)
        {
            SpeakerText->SetText(Row->SpeakerName);
        }
        if (DialogueText)
        {
            DialogueText->SetText(Row->DialogueText);
        }
        if (CurrentRow.bPlaySound && CurrentRow.DialogueSound)
        {
            UGameplayStatics::PlaySound2D(this, CurrentRow.DialogueSound);
        }

        InvalidateLayoutAndVolatility();
    }
}
