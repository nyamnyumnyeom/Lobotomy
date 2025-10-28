#include "LB_LockDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Character/LB_Character.h"

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

    bIsOpen = false;
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
        OpenDoor();
        UE_LOG(LogTemp, Warning, TEXT("Unlocked door with key: %s"), *HeldItem.ToString());
        return true;
    }

    UE_LOG(LogTemp, Warning, TEXT("Wrong key: %s (Required: %s)"),
        *HeldItem.ToString(), *RequiredKey.ToString());
    return false;
}