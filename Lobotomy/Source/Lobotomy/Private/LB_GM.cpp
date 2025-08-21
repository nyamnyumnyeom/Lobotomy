#include "LB_GM.h"
#include "Character/LB_PlayerController.h"
#include "Character/LB_Character.h"

ALB_GM::ALB_GM()
{
    DefaultPawnClass = ALB_Character::StaticClass();
    PlayerControllerClass = ALB_PlayerController::StaticClass();
}

void ALB_GM::BeginPlay()
{
    Super::BeginPlay();
}