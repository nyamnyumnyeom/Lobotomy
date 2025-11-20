#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class UWidgetComponent;
class UTextRenderComponent;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOBOTOMY_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

	void ShowWidget();
	void HideWidget();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact(AActor* InteractingActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interact")
	void OnInteractBPevent();

	UFUNCTION(BlueprintImplementableEvent)
	void InteractFunction(AActor* InteractingActor);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction|Components")
	TObjectPtr<UTextRenderComponent> InteractionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	FText DisplayText = FText::FromString(TEXT("Press E"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	float WidgetDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	FVector WidgetStaticOffset = FVector(0.f, 0.f, 50.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	float UpdateInterval = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	float DefaultSize = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|UI")
	float SizeScaleFactor = 1.0f;
private:
	FTimerHandle LookAtTimerHandle;

	void UpdateWidgetTransform();

	void UpdateWidgetSize();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	UMaterialInterface* OverlayMaterial;

	UPROPERTY()
	TArray<UMeshComponent*> Meshes;

	UPROPERTY()
	TArray<UMaterialInterface*> OriginalOverlayMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlayui")
	bool isoverlayok = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "interact")
	bool interactbp = false;

private:
	void CollectAllMeshes(AActor* Actor);
	void SetOverlayVisible(bool bVisible);
};