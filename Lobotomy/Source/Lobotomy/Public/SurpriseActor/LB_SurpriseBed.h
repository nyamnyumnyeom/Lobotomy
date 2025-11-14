// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurpriseActor/LB_SurpriseBase.h"
#include "LB_SurpriseBed.generated.h"

/**
 * 
 */
UCLASS()
class LOBOTOMY_API ALB_SurpriseBed : public ALB_SurpriseBase
{
	GENERATED_BODY()
	
protected:
	// 침대 아래에 등장할 손
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* SkeletalMeshComp;

	// 이벤트가 발생할 때 재생시킬 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* SurpriseSound;

	// 이벤트가 발생할 때 재생시킬 애니메이션}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* SurpriseMontage;

public:
	// 한번 이벤트가 작동한 뒤, 다시 작동이 가능하도록 하는데 걸리는 시간
	float ResetTime = 30.0f;

protected:
	bool bCanSurprise = true;

protected:
	FTimerHandle ResetTimerHandle;

public:
	ALB_SurpriseBed();

protected:
	virtual void SurprisEventStart() override;

protected:
	void PlaySound_Surprise();

	void PlayAnimation_Surprise();

protected:
	void Surprise_Reset();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetbCanSurprise() const { return bCanSurprise; }

};
