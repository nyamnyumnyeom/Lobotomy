#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LB_GM.generated.h"

UCLASS()
class LOBOTOMY_API ALB_GM : public AGameMode
{
	GENERATED_BODY()
	
public:
	ALB_GM();

protected:
	virtual void BeginPlay() override;
};
