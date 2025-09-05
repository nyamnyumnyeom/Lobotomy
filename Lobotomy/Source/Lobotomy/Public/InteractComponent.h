#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class UWidgetComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

	void ShowWidget();
	void HideWidget();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction|Components")
	TObjectPtr<UWidgetComponent> InteractionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	TSubclassOf<UUserWidget> DefaultWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	float WidgetDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	FVector WidgetStaticOffset = FVector(0.f, 0.f, 50.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	float UpdateInterval = 0.05f;

private:
	FTimerHandle LookAtTimerHandle;

	void UpdateWidgetTransform();
};