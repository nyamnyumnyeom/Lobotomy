#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Wardrobewidget.generated.h"


UCLASS()
class LOBOTOMY_API UWardrobewidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wardrobe")
	TSubclassOf<AActor> WardrobeClass;

	UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	AActor* FindNearestActorOfClass(TSubclassOf<AActor> TargetClass) const;

	//UFUNCTION(BlueprintCallable, Category = "Wardrobe")
	//AActor* FindNearestWardrobe() const;
};
