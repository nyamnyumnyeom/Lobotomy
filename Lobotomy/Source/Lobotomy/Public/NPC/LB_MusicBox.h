// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_MusicBox.generated.h"

UCLASS()
class LOBOTOMY_API ALB_MusicBox : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	class UAudioComponent* AudioComp;

	// 오르골 소리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	class USoundBase* MusicSound;

protected:
	FTimerHandle NoiseTimerHandle;

public:	
	ALB_MusicBox();

protected:
	virtual void BeginPlay() override;

public:
	// 상호작용으로 음악 종료
	UFUNCTION(BlueprintCallable)
	void MusicOff();

	UFUNCTION(BlueprintImplementableEvent)
	void MakeNoiseForAI();

};
