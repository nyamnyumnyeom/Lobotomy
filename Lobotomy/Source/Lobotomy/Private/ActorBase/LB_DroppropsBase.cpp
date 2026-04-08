#include "ActorBase/LB_DroppropsBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ALB_DroppropsBase::ALB_DroppropsBase()
{
    PrimaryActorTick.bCanEverTick = false;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;

    DropDirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DropDirectionArrow"));
    DropDirectionArrow->SetupAttachment(BaseMesh);

    BaseMesh->SetSimulatePhysics(false);
    BaseMesh->SetNotifyRigidBodyCollision(true);
}

void ALB_DroppropsBase::BeginPlay()
{
    Super::BeginPlay();

    GetComponents<UStaticMeshComponent>(CachedMeshComponents);

    for (UStaticMeshComponent* MeshComp : CachedMeshComponents)
    {
        if (!MeshComp) continue;

        MeshComp->SetNotifyRigidBodyCollision(true);
        MeshComp->OnComponentHit.AddDynamic(this, &ALB_DroppropsBase::OnMeshHit);

        InitialMeshWorldTransforms.Add(MeshComp, MeshComp->GetComponentTransform());
    }
}

void ALB_DroppropsBase::Dropforce()
{
    const FVector DropDirection = DropDirectionArrow->GetForwardVector();
    const FVector Impulse = DropDirection * DropForceMagnitude;

    for (UStaticMeshComponent* MeshComp : CachedMeshComponents)
    {
        if (!MeshComp) continue;

        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetNotifyRigidBodyCollision(true);
        MeshComp->AddImpulse(Impulse, NAME_None, true);
    }
}

void ALB_DroppropsBase::ResetDropProps()
{
    for (UStaticMeshComponent* MeshComp : CachedMeshComponents)
    {
        if (!MeshComp) continue;

        MeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
        MeshComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
        MeshComp->SetSimulatePhysics(false);

        if (const FTransform* InitialTransform = InitialMeshWorldTransforms.Find(MeshComp))
        {
            MeshComp->SetWorldTransform(*InitialTransform, false, nullptr, ETeleportType::TeleportPhysics);
        }
    }

    LastImpactSoundTime = -1000.0f;
}

void ALB_DroppropsBase::OnMeshHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (!DropImpactSound) return;
    if (!HitComponent) return;
    if (OtherActor == this) return;
    if (!GetWorld()) return;

    const float ImpactStrength = NormalImpulse.Size();
    if (ImpactStrength < MinImpactStrengthForSound) return;

    const float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastImpactSoundTime < ImpactSoundCooldown) return;

    LastImpactSoundTime = CurrentTime;

    const float ClampedImpact = FMath::Clamp(
        ImpactStrength,
        MinImpactStrengthForSound,
        MaxImpactStrengthForSound
    );

    const float NormalizedImpact = FMath::GetRangePct(
        MinImpactStrengthForSound,
        MaxImpactStrengthForSound,
        ClampedImpact
    );

    const float VolumeMultiplier = FMath::Lerp(
        MinVolumeMultiplier,
        MaxVolumeMultiplier,
        NormalizedImpact
    );

    const float PitchMultiplier = FMath::Lerp(
        MinPitchMultiplier,
        MaxPitchMultiplier,
        NormalizedImpact
    );

    if (UAudioComponent* AudioComp = UGameplayStatics::SpawnSoundAtLocation(
        this,
        DropImpactSound,
        Hit.ImpactPoint
    ))
    {
        AudioComp->SetVolumeMultiplier(VolumeMultiplier);
        AudioComp->SetPitchMultiplier(PitchMultiplier);
    }
}