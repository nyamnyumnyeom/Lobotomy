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

protected:
	virtual void BeginPlay() override;
};
