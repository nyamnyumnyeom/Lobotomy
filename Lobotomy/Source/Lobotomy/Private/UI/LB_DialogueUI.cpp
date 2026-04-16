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

    FName NextDialogueID = CurrentRow.NextID;

    if (CurrentRow.bUseInventoryBranch)
    {
        if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
        {
            if (ALB_Character* Player = Cast<ALB_Character>(PC->GetPawn()))
            {
                // 이미 아이템을 받은 상태면 분기 무시, 그냥 원래 NextID 유지
                if (!Player->bReceivedpjwReward)
                {
                    if (!Player->HasAnyItem())
                    {
                        bool bGiveSuccess = false;

                        if (!CurrentRow.RewardItemID.IsNone())
                        {
                            bGiveSuccess = Player->GiveItemByID(CurrentRow.RewardItemID);
                        }

                        if (bGiveSuccess)
                        {
                            Player->bReceivedpjwReward = true;
                            NextDialogueID = CurrentRow.EmptyInventoryNextID;
                        }
                        else
                        {
                            NextDialogueID = CurrentRow.OccupiedInventoryNextID;
                        }
                    }
                    else
                    {
                        NextDialogueID = CurrentRow.OccupiedInventoryNextID;
                    }
                }
            }
        }
    }

    FDialogueRow* NextRow = nullptr;

    if (!NextDialogueID.IsNone())
    {
        NextRow = DialogueTable->FindRow<FDialogueRow>(NextDialogueID, TEXT("ShowNextDialogue"));
    }

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
                PC->bShowMouseCursor = true;

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
