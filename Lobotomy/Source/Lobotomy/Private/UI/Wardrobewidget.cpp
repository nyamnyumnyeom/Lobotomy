#include "UI/Wardrobewidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

AActor* UWardrobewidget::FindNearestActorOfClass(TSubclassOf<AActor> TargetClass) const
{
	UWorld* World = GetWorld();
	if (!World || !TargetClass)
	{
		return nullptr;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	if (!PlayerPawn)
	{
		return nullptr;
	}

	const FVector PlayerLoc = PlayerPawn->GetActorLocation();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, TargetClass, FoundActors);

	AActor* ClosestActor = nullptr;
	float MinDistSq = TNumericLimits<float>::Max();

	for (AActor* Actor : FoundActors)
	{
		if (!Actor) continue;

		const float DistSq = FVector::DistSquared(PlayerLoc, Actor->GetActorLocation());
		if (DistSq < MinDistSq)
		{
			MinDistSq = DistSq;
			ClosestActor = Actor;
		}
	}

	return ClosestActor;
}
//
//AActor* UWardrobeWidget::FindNearestWardrobe() const
//{
//	return FindNearestActorOfClass(WardrobeClass);
//}