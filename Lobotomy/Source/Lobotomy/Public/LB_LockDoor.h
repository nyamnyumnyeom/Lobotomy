#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_LockDoor.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class ALB_Character;

UCLASS()
class LOBOTOMY_API ALB_LockDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALB_LockDoor();

public:
    // 문이 열려있는지 여부
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
    bool bIsOpen;

    // 해당 문을 열 수 있는 키 이름 (아이템 데이터 테이블의 ItemCode)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    FName RequiredKey;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* DoorMesh;

	// 소리
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Music")
	class UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> OpenSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> CloseSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> AutoOpenSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<class USoundBase*> ChainSawManOpenSounds;

    // 실제 문 로직
    UFUNCTION(BlueprintCallable, Category = "Door")
    void OpenDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    void CloseDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    bool TryUnlockDoor(ALB_Character* PlayerCharacter);
};
