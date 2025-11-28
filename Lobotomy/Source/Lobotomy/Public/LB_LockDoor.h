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

	// 문 고리에 놓을 UI 관련 코드
protected:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* DoorHandleWidget;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDoorHandleWidgetFadeIn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDoorHandleWidgetFadeOut();

	// 전기톱, 걷는 환자 관련 코드.
public:
	FTimerHandle OpenLoopTimerHandle;

	// 전기톱, 걷는 환자가 비긴오버랩되면 문 열기.
	UFUNCTION(BlueprintImplementableEvent)
	void OnWalkerBeginOverlap();

	// 전기톱, 걷는 환자가 엔드오버랩되면 문 닫기
	UFUNCTION(BlueprintImplementableEvent)
	void OnWalkerEndOverlap();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	class USoundBase* UnlockSound;

	// [0 : 열리는 소리], [1 : 닫히는 소리], [2 : 자동 열림 소리], [3 : 전기톱이 열때 소리]
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlayDoorSound(int32 SoundValue);

	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlayUnlockSound();

    // 실제 문 로직
    UFUNCTION(BlueprintCallable, Category = "Door")
    void OpenDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    void CloseDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    bool TryUnlockDoor(ALB_Character* PlayerCharacter);
};
