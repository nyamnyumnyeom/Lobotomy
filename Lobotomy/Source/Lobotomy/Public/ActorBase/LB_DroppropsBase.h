#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_DroppropsBase.generated.h"


class UArrowComponent;
class UStaticMeshComponent;

UCLASS()
class LOBOTOMY_API ALB_DroppropsBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ALB_DroppropsBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop")
	UStaticMeshComponent* BaseMesh;

	UFUNCTION(BlueprintCallable, Category = "Drop")
	void Dropforce();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	float DropForceMagnitude = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drop")
	UArrowComponent* DropDirectionArrow;
};
