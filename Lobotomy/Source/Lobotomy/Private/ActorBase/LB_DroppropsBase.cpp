#include "ActorBase/LB_DroppropsBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

ALB_DroppropsBase::ALB_DroppropsBase()
{
    PrimaryActorTick.bCanEverTick = false;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    DropDirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DropDirectionArrow"));
    DropDirectionArrow->SetupAttachment(BaseMesh);

    BaseMesh->SetSimulatePhysics(false);
}

void ALB_DroppropsBase::Dropforce()
{
    const FVector DropDirection = DropDirectionArrow->GetForwardVector();

    TArray<UStaticMeshComponent*> MeshComponents;
    GetComponents<UStaticMeshComponent>(MeshComponents);

    for (UStaticMeshComponent* MeshComp : MeshComponents)
    {
        if (!MeshComp) continue;

        MeshComp->SetSimulatePhysics(true);

        const FVector Impulse = DropDirection * DropForceMagnitude;
        MeshComp->AddImpulse(Impulse, NAME_None, true);
    }
}
