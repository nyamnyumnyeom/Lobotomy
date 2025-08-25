#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MediaPlayer.h"
#include "MediaSource.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartClicked);
	}
	if (OptionButton)
	{
		OptionButton->OnClicked.AddDynamic(this, &UMainMenu::OnOptionClicked);
	}
	if (CreditButton)
	{
		CreditButton->OnClicked.AddDynamic(this, &UMainMenu::OnCreditClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenu::OnExitClicked);
	}

	if (MediaPlayer && MediaSource)
	{
		MediaPlayer->OpenSource(MediaSource);
		MediaPlayer->Play();
	}
}

void UMainMenu::OnStartClicked()
{
	if (!StartLevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, StartLevelName);
	}
}

void UMainMenu::OnOptionClicked()
{
	// 可记 困连 剁快扁 (眠饶 备泅)
	UE_LOG(LogTemp, Log, TEXT("Option Menu Open"));
}

void UMainMenu::OnCreditClicked()
{
	// 农饭调 困连 剁快扁 (眠饶 备泅)
	UE_LOG(LogTemp, Log, TEXT("Credit Menu Open"));
}

void UMainMenu::OnExitClicked()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->ConsoleCommand("quit");
	}
}