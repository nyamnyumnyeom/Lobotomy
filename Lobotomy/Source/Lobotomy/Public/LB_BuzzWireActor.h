#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_BuzzWireActor.generated.h"

class UCameraComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UCapsuleComponent;

UCLASS()
class LOBOTOMY_API ALB_BuzzWireActor : public AActor
{
	GENERATED_BODY()

public:
	ALB_BuzzWireActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "BuzzWire")
	void BuzzPlay(float BlendTime = 0.35f);

	UFUNCTION(BlueprintCallable, Category = "BuzzWire")
	void BuzzStop(float BlendTime = 0.25f);

	UFUNCTION(BlueprintCallable, Category = "BuzzWire")
	void SetBuzzActive(bool bNewActive);

	UFUNCTION(BlueprintImplementableEvent, Category = "BuzzWire")
	void OnBuzzDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "BuzzWire")
	void OnBuzzSuccess();

	UFUNCTION(BlueprintImplementableEvent, Category = "BuzzWire")
	void OnSPZone1();

	UFUNCTION(BlueprintImplementableEvent, Category = "BuzzWire")
	void OnSPZone2();

	UFUNCTION(BlueprintImplementableEvent, Category = "BuzzWire")
	void OnSPZone3();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UCameraComponent* FocusCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UStaticMeshComponent* RingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UCapsuleComponent* InCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UCapsuleComponent* OutCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UStaticMeshComponent* DeadZoneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UBoxComponent* SuccessZoneCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UBoxComponent* SPZone1Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UBoxComponent* SPZone2Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|Components")
	UBoxComponent* SPZone3Collision;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuzzWire|DistanceCheck")
	USplineComponent* TargetSpline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuzzWire|DistanceCheck")
	float DangerRadius = 4.5f;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuzzWire|Mouse Follow")
	TEnumAsByte<ECollisionChannel> MouseTraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuzzWire|Mouse Follow")
	float FollowInterpSpeed = 25.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuzzWire|Mouse Follow")
	FVector RingWorldOffset = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|State")
	bool bBuzzActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|State")
	bool bDeadTriggered = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuzzWire|State")
	bool bSuccessTriggered = false;

private:
	UPROPERTY()
	APlayerController* CachedPC = nullptr;

	UPROPERTY()
	AActor* PreviousViewTarget = nullptr;

	void ApplyMouseOnlyInputLock(APlayerController* PC);
	void RestoreInput(APlayerController* PC);
	void UpdateRingFollowMouse(float DeltaSeconds);
	//void CheckDistanceToRod();

	UFUNCTION()
	void HandleSuccessZoneBeginOverlap(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleSPZone1BeginOverlap(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleSPZone2BeginOverlap(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleSPZone3BeginOverlap(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EndBuzzSession();

	UFUNCTION()
	void HandleInBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleInEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void HandleOutBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleOutEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void EvaluateDead();


	//회전함수
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuzzWire|Rotate")
		float RingRotationStep = 2.0f;

protected:
	void RotateRingUp();
	void RotateRingDown();

	bool bInOverlap = false;
	bool bOutOverlap = false;
};