#include "InteractComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "TimerManager.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InteractionText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InteractionText"));
	InteractionText->SetHorizontalAlignment(EHTA_Center);
	InteractionText->SetVerticalAlignment(EVRTA_TextCenter);
	InteractionText->SetTextRenderColor(FColor::White);
	InteractionText->SetWorldSize(30.f);
	InteractionText->SetVisibility(false);
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		TArray<UMeshComponent*> FoundMeshes;
		Owner->GetComponents<UMeshComponent>(FoundMeshes);

		for (auto* M : FoundMeshes)
		{
			if (M)
			{
				Meshes.Add(M);
				OriginalOverlayMaterials.Add(M->GetOverlayMaterial());
			}
		}
	}

	if (AActor* Owner = GetOwner())
	{
		if (USceneComponent* Root = Owner->GetRootComponent())
		{
			InteractionText->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
			InteractionText->SetRelativeLocation(WidgetStaticOffset);
		}
	}

	// 초기 텍스트 설정
	if (InteractionText)
	{
		InteractionText->SetText(DisplayText);
		InteractionText->SetVisibility(false);
	}
}

void UInteractComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(LookAtTimerHandle);
	}
}

void UInteractComponent::ShowWidget()
{
	if (InteractionText)
	{
		InteractionText->SetVisibility(true);

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(
				LookAtTimerHandle,
				this,
				&UInteractComponent::UpdateWidgetTransform,
				UpdateInterval,
				true
			);
		}
	}
	if (isoverlayok)
	{
	
	SetOverlayVisible(true);
	}
}

void UInteractComponent::HideWidget()
{
	if (InteractionText)
	{
		InteractionText->SetVisibility(false);
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(LookAtTimerHandle);
		}
	}
	if (isoverlayok)
	{

		SetOverlayVisible(false);
	}
}


void UInteractComponent::CollectAllMeshes(AActor* Actor)
{
	if (!Actor) return;

	TArray<UActorComponent*> Components = Actor->GetComponents().Array();

	for (UActorComponent* Comp : Components)
	{
		if (UMeshComponent* Mesh = Cast<UMeshComponent>(Comp))
		{
			if (Mesh->IsA(UInstancedStaticMeshComponent::StaticClass()) ||
				Mesh->IsA(UHierarchicalInstancedStaticMeshComponent::StaticClass()))
			{
				continue;
			}

			Meshes.Add(Mesh);
			OriginalOverlayMaterials.Add(Mesh->GetOverlayMaterial());
		}
	}

	TArray<UChildActorComponent*> ChildActors;
	Actor->GetComponents<UChildActorComponent>(ChildActors);

	for (UChildActorComponent* Child : ChildActors)
	{
		if (AActor* ChildActor = Child->GetChildActor())
		{
			CollectAllMeshes(ChildActor);
		}
	}
}

void UInteractComponent::SetOverlayVisible(bool bVisible)
{
	for (int32 i = 0; i < Meshes.Num(); i++)
	{
		UMeshComponent* Mesh = Meshes[i];
		if (!Mesh) continue;

		if (bVisible)
		{
			if (OverlayMaterial)
			{
				Mesh->SetOverlayMaterial(OverlayMaterial);
			}
		}
		else
		{
			UMaterialInterface* OrigMat =
				OriginalOverlayMaterials.IsValidIndex(i)
				? OriginalOverlayMaterials[i]
				: nullptr;

			Mesh->SetOverlayMaterial(OrigMat);
		}
	}
}



void UInteractComponent::UpdateWidgetTransform()
{
	if (!InteractionText || !InteractionText->IsVisible()) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* Owner = GetOwner();
	if (!PC || !PC->GetPawn() || !Owner) return;

	FVector PlayerLocation = PC->GetPawn()->GetActorLocation();

	FVector Origin, Extent;
	Owner->GetActorBounds(true, Origin, Extent);

	FVector BaseLocation = Origin + FVector(0.f, 0.f, Extent.Z);
	FVector DirectionToPlayer = (PlayerLocation - BaseLocation).GetSafeNormal();

	FVector NewWorldLocation = BaseLocation + (DirectionToPlayer * WidgetDistance) + WidgetStaticOffset;
	InteractionText->SetWorldLocation(NewWorldLocation);

	FVector ToPlayerFromText = PlayerLocation - InteractionText->GetComponentLocation();
	FRotator LookAtRot = ToPlayerFromText.Rotation();
	InteractionText->SetWorldRotation(LookAtRot);

	UpdateWidgetSize();

			/*FVector BoundsOrigin, BoundsExtent;
			SizeComp->GetOwner()->GetActorBounds(false, BoundsOrigin, BoundsExtent);
			float MaxExtent = BoundsExtent.GetMax();
			InteractionText->SetWorldSize(MaxExtent * 0.2f);*/
}

void UInteractComponent::UpdateWidgetSize()
{
	if (!InteractionText) return;

	if (AActor* Owner = GetOwner())
	{
		TArray<USceneComponent*> Components;
		Owner->GetComponents<USceneComponent>(Components);

		for (USceneComponent* Comp : Components)
		{
			if (Comp && Comp->GetName() == TEXT("Size"))
			{
				float ScaleFactor = Comp->GetComponentScale().GetMax();

				InteractionText->SetWorldSize(DefaultSize * ScaleFactor * SizeScaleFactor);
				return;
			}
		}
	}
	InteractionText->SetWorldSize(DefaultSize);
}

void UInteractComponent::Interact(AActor* InteractingActor)
{
	if (!InteractingActor) return;

	InteractFunction(InteractingActor);

	UE_LOG(LogTemp, Error, TEXT("%s interact ok~~ - %s"),
		*InteractingActor->GetName(), *GetOwner()->GetName());

}