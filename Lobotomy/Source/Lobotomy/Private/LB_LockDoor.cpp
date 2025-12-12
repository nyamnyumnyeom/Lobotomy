#include "LB_LockDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Character/LB_Character.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

ALB_LockDoor::ALB_LockDoor()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = Root;

    // 문 메쉬 생성 및 부착
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(Root);

    // 기본 충돌 설정 (캐릭터 막기)
    DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DoorMesh->SetCollisionResponseToAllChannels(ECR_Block);
    DoorMesh->SetCollisionObjectType(ECC_WorldStatic);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->bAutoActivate = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	SphereCollision->InitSphereRadius(300.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALB_LockDoor::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ALB_LockDoor::OnOverlapEnd);

	DoorHandleWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DoorHandleWidget"));
	DoorHandleWidget->SetupAttachment(SphereCollision);

    bIsOpen = false;
	bIsLeft = true;

	Tags.Add(FName("Door"));
}

void ALB_LockDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	/*if (OtherActor->ActorHasTag("Player"))
	{
		OnDoorHandleWidgetFadeIn();
	}*/

	if (OtherActor->ActorHasTag("DoorPass"))
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(OpenLoopTimerHandle, this, &ALB_LockDoor::OnWalkerBeginOverlap, 1.0f, true);
		}
	}
}

void ALB_LockDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	/*if (OtherActor->ActorHasTag("Player"))
	{
		OnDoorHandleWidgetFadeOut();
	}*/

	if (OtherActor->ActorHasTag("DoorPass"))
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(OpenLoopTimerHandle);

			OnWalkerEndOverlap();
		}
	}
}

void ALB_LockDoor::PlayDoorSound(int32 SoundValue)
{
	TArray<USoundBase*> CurrentSoundBases;

	switch (SoundValue)
	{
	case 0:
		CurrentSoundBases = OpenSounds;
		break;

	case 1:
		CurrentSoundBases = CloseSounds;
		break;

	case 2:
		CurrentSoundBases = AutoOpenSounds;
		break;

	case 3:
		CurrentSoundBases = ChainSawManOpenSounds;
		break;

	default:
		break;
	}

	if (!IsValid(CurrentSoundBases[0])) return;

	int32 RandomIndex = FMath::RandRange(0, CurrentSoundBases.Num() - 1);
	if (CurrentSoundBases[RandomIndex] && AudioComp)
	{
		AudioComp->SetSound(CurrentSoundBases[RandomIndex]);
		AudioComp->Play();
	}
}

void ALB_LockDoor::PlayUnlockSound()
{
	if (UnlockSound && AudioComp)
	{
		AudioComp->SetSound(UnlockSound);
		AudioComp->Play();
	}
}

void ALB_LockDoor::OpenDoor()
{
    if (bIsOpen) return;
    bIsOpen = true;

    UE_LOG(LogTemp, Warning, TEXT("Door opened."));
}

void ALB_LockDoor::CloseDoor()
{
    if (!bIsOpen) return;
    bIsOpen = false;

    UE_LOG(LogTemp, Warning, TEXT("Door closed."));
}

void ALB_LockDoor::LeftOpenDesk()
{
	if (bIsLeft) return;
	bIsLeft = true;
	UE_LOG(LogTemp, Warning, TEXT("Left door opened."));
}

void ALB_LockDoor::RightOpenDesk()
{
	if (!bIsLeft) return;
	bIsLeft = false;
	UE_LOG(LogTemp, Warning, TEXT("Right door opened."));
}

bool ALB_LockDoor::TryUnlockDoor(ALB_Character* PlayerCharacter)
{
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("No player reference."));
        return false;
    }

    if (bIsOpen)
    {
        UE_LOG(LogTemp, Warning, TEXT("Door already open."));
        return false;
    }

    FName HeldItem = PlayerCharacter->CurrentItem;

    if (HeldItem == NAME_None)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player has no item."));
        return false;
    }

    if (HeldItem == RequiredKey)
    {
        //OpenDoor();
        UE_LOG(LogTemp, Warning, TEXT("Unlocked door with key: %s"), *HeldItem.ToString());
        return true;
    }

    UE_LOG(LogTemp, Warning, TEXT("Wrong key: %s (Required: %s)"),
        *HeldItem.ToString(), *RequiredKey.ToString());
    return false;
}

