#include "LB_FootSteps_Paitent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

void ULB_FootSteps_Paitent::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp || !FootstepSound)
		return;

	float RandomPitch = FMath::FRandRange(PitchMin, PitchMax);

	UGameplayStatics::PlaySoundAtLocation(
		this,
		FootstepSound,
		MeshComp->GetComponentLocation(),
		VolumeMultiplier,
		RandomPitch
	);
}