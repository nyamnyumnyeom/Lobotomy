#include "Character/LB_PlayerController.h"
#include "EnhancedInputSubsystems.h"

ALB_PlayerController::ALB_PlayerController()
:InputMappingContext(nullptr),
 MoveAction(nullptr),
 LookAction(nullptr),
 SprintAction(nullptr)
{
}

void ALB_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}