#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LB_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class LOBOTOMY_API ALB_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALB_PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* EscapeAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FlashlightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UseItemAction;
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetMouseSensitivite(float NewSensitivie);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	float CurrentSensitivite = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ChartAction;

protected:
	virtual void BeginPlay() override;
};
