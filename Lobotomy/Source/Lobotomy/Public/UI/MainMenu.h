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
	// ������ �ʱ�ȭ�� �� ȣ��
	virtual void NativeConstruct() override;

public:
	/** ��ư ������ (�����̳ʿ��� ���ε� �ʿ�) */
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CreditButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	/** �����Ϳ��� ���� ������ ���� �� �̸� */
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