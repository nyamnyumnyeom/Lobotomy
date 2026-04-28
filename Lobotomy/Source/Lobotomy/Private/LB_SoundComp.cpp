#include "LB_SoundComp.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ULB_SoundComp::ULB_SoundComp()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void ULB_SoundComp::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (!Owner) return;

    Owner->GetComponents<UStaticMeshComponent>(CachedMeshComponents);

    for (UStaticMeshComponent* MeshComp : CachedMeshComponents)
    {
        if (!MeshComp) continue;

        MeshComp->SetNotifyRigidBodyCollision(true);
        MeshComp->OnComponentHit.AddDynamic(this, &ULB_SoundComp::OnMeshHit);
    }
}

void ULB_SoundComp::OnMeshHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (!ImpactSound) return;
    if (!HitComponent) return;
    if (!OtherActor) return;
    if (OtherActor == GetOwner()) return;
    if (!GetWorld()) return;

    const float ImpactStrength = NormalImpulse.Size();

    if (ImpactStrength < MinImpactStrengthForSound)
    {
        return;
    }

    const float CurrentTime = GetWorld()->GetTimeSeconds();

    if (CurrentTime - LastImpactSoundTime < ImpactSoundCooldown)
    {
        return;
    }

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
        ImpactSound,
        Hit.ImpactPoint
    ))
    {
        AudioComp->SetVolumeMultiplier(VolumeMultiplier);
        AudioComp->SetPitchMultiplier(PitchMultiplier);
    }
}