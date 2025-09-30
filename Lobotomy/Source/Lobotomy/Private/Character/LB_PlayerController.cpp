#include "Character/LB_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "LB_Setting.h"
#include "UI/LB_SettingUI.h"

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

void ALB_PlayerController::UpdateMouseSensitivity()
{
    if (!LookAction) return;

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            float Sensitivity = 1.f;
            if (ULB_Setting* Settings = ULB_Setting::Get())
            {
                Sensitivity = Settings->MouseSensitivity;
            }

            Subsystem->SetInputScale(LookAction, Sensitivity);
        }
    }
}
