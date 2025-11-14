#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UMediaPlayer;
class UMediaSource;

UCLASS()
class LOBOTOMY_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// 위젯이 초기화될 때 호출
	virtual void NativeConstruct() override;

public:
	/** 버튼 위젯들 (디자이너에서 바인딩 필요) */
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CreditButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	/** 에디터에서 변경 가능한 시작 맵 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu")
	FName StartLevelName = "ExampleMap";

private:
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnOptionClicked();

	UFUNCTION()
	void OnCreditClicked();

	UFUNCTION()
	void OnExitClicked();
};