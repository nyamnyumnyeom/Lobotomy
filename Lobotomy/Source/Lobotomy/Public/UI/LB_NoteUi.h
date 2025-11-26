// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "LB_NoteUi.generated.h"


UCLASS()
class LOBOTOMY_API ULB_NoteUi : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    /** 텍스트 블럭들 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* NameText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* SymptomText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* RemarkText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* PageNumberText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* RoomText; 

    /** 체크박스들 (Day01 ~ Day07) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day01;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day02;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day03;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day04;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day05;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day06;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCheckBox* Day07;

	/** 체크박스들 (Night01 ~ Night07) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night03;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night04;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night05;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night06;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Night07;

    /** 데이터 업데이트 함수들 */
    UFUNCTION(BlueprintCallable, Category = "Medical Record")
    void SetName(const FText& NewName);

    UFUNCTION(BlueprintCallable, Category = "Medical Record")
    void SetSymptom(const FText& NewSymptom);

    UFUNCTION(BlueprintCallable, Category = "Medical Record")
    void SetRemark(const FText& NewRemark);

    UFUNCTION(BlueprintCallable, Category = "Medical Record")
    void SetPageNumber(int32 PageNumber);

    UFUNCTION(BlueprintCallable, Category = "Medical Record")
    void SetDayChecked(int32 DayIndex, bool bChecked);

    UFUNCTION() void HandleChartUpdated(int32 PageNumber);

    UFUNCTION(BlueprintCallable, Category = "Medical Record")
    void RefreshFromGameMode();
};
