#include "InteractComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::World);
	InteractionWidget->SetDrawSize(FVector2D(200.f, 100.f));
	InteractionWidget->SetVisibility(false);
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		if (USceneComponent* Root = Owner->GetRootComponent())
		{
			InteractionWidget->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
			InteractionWidget->SetRelativeLocation(WidgetStaticOffset);
		}
	}

	if (InteractionWidget && DefaultWidgetClass)
	{
		InteractionWidget->SetWidgetClass(DefaultWidgetClass);
	}
	InteractionWidget->SetVisibility(false);
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
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(true);

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
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(false);
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(LookAtTimerHandle);
		}
	}
}

void UInteractComponent::UpdateWidgetTransform()
{
	if (!InteractionWidget || !InteractionWidget->IsVisible()) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* Owner = GetOwner();
	if (!PC || !PC->GetPawn() || !Owner) return;

	FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
	FVector OwnerLocation = Owner->GetActorLocation();

	FVector DirectionToPlayer = (PlayerLocation - OwnerLocation).GetSafeNormal();

	FVector NewRelativeLocation = (DirectionToPlayer * WidgetDistance) + WidgetStaticOffset;
	InteractionWidget->SetRelativeLocation(NewRelativeLocation);

	FVector ToPlayerFromWidget = PlayerLocation - InteractionWidget->GetComponentLocation();
	FRotator LookAtRot = ToPlayerFromWidget.Rotation();
	InteractionWidget->SetWorldRotation(LookAtRot);
}