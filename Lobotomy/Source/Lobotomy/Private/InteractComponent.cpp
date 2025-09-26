#include "InteractComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
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

	UE_LOG(LogTemp, Error, TEXT("%s 상호작용됨 - %s"),
		*InteractingActor->GetName(), *GetOwner()->GetName());

	// 여기서 실제 게임 로직 추가 가능
	// 예: 아이템 획득, 문 열기, 버튼 작동 등
}