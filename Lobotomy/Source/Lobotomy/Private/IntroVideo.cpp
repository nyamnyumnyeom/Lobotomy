#include "IntroVideo.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "MediaPlayer.h"
#include "MediaSource.h"

void UIntroVideo::NativeConstruct()
{
    Super::NativeConstruct();

    if (MediaPlayer && MediaSource)
    {
        MediaPlayer->OnEndReached.AddDynamic(this, &UIntroVideo::OnIntroFinished);
        MediaPlayer->OpenSource(MediaSource);
        MediaPlayer->Play();
    }
}

void UIntroVideo::OnIntroFinished()
{
    RemoveFromParent();

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (MainMenuClass)
        {
            UMainMenu* Menu = CreateWidget<UMainMenu>(PC, MainMenuClass);
            if (Menu)
            {
                Menu->AddToViewport();
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("MainMenuClass is not set in IntroWidget!"));
        }
    }
}