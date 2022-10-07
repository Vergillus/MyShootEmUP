// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Public/GrenadeBase.h"
#include "MYPawn.generated.h"

class UFloatingPawnMovement;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class AMYCharacterBase;
class UHealthComponent;
class AMYCharacterBase;
class UCurveFloat;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaderChanged);

UCLASS()
class MYSHOOTEMUP_API AMYPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMYPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category= "Movement")
	UFloatingPawnMovement* PawnMovementComp;

	UPROPERTY(EditAnywhere, Category= "Collision")
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere, Category= "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category= "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	UDecalComponent* DecalComponent;

	/* We do not rotate the root component so we rotate this components to rotate squad */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Movement")
	USceneComponent* RotParentByMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Movement")
	USceneComponent* SquadParent;

	UPROPERTY(EditDefaultsOnly)
	TArray<UStaticMeshComponent*> SquadMemberPositions;

#pragma region Movement Related Functions

	UFUNCTION(BlueprintCallable, Category= "Pawn Movement")
	void MoveForwardBack(float AxisVal);

	UFUNCTION(BlueprintCallable, Category= "Pawn Movement")
	void MoveLeftRight(float AxisVal);

	UFUNCTION(BlueprintCallable, Category= "Pawn Movement")
	void RotateSquadMembers();

	UFUNCTION()
	void RotateSquadInTime(const float Duration, const FRotator CurrentRot, const FRotator DesiredRot);

#pragma endregion

	FTimerHandle CharacterRotationTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category= "Character Rotation")
	float CharacterRotationDuration;
	float CharacterRotLerpVal;
	bool bCanRotateCharacters;

	int CurrentLeaderIndex;

#pragma  region Grenade Related 

	UPROPERTY(BlueprintReadOnly)
	bool bCanThrowGrenade;
	
	FVector2d CachedMousePos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	float GrenadeThrowHeight;

	void GrenadeThrowStart();
	void ThrowGrenade();
	void GrenadeThrowEnd();

	void VisualizeGrenadeTrajectory(const FVector StartPos, const FVector EndPos) const;
	TArray<FVector> CalculateGrenadePath(const FVector StartPos, const FVector EndPos) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Grenade")
	TSubclassOf<AGrenadeBase> GrenadeToSpawn;
	
	UFUNCTION(BlueprintCallable)
	void ChangeTimeDilations(bool bUseSlowMo);

	// Implemented in the BP of this class
	UFUNCTION(BlueprintImplementableEvent)
	void StartSlowMoTimer();

	// Implemented in the BP of this class
	UFUNCTION(BlueprintImplementableEvent)
	void StopSlowMoTimer();

	UPROPERTY(EditDefaultsOnly, Category= "Grenade")
	float SpringArmMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category= "Grenade")
	float MaxGrenadeThrowDistance;

	UPROPERTY(EditDefaultsOnly, Category= "Grenade")
	float MaxGrenadeCount;

	UPROPERTY(EditDefaultsOnly, Category= "Grenade")
	float CurrentGrenadeCount;

#pragma endregion

	bool bCanFire;
	
	void StartFire();
	void EndFire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UChildActorComponent*> SquadMembers;

	int AliveMembersCount;

	UFUNCTION(BlueprintCallable)
	void ChangeLeader();	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input //
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MemberDeath(bool bIsLeaderDead = false);

	FORCEINLINE void GrenadePickedUp() { CurrentGrenadeCount = FMath::Min(CurrentGrenadeCount + 1, MaxGrenadeCount) ;}

	
	FOnLeaderChanged OnLeaderChanged;

};
