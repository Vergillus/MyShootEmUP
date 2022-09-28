// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class USphereComponent;

UCLASS(Abstract)
class MYSHOOTEMUP_API ABasePickUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePickUp();

private:
	/* Mesh of the pick up item */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;

	/* Sphere component that checks for the overlapped actors. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollider;

protected:
	
	virtual void OnPicked();

	/* Function to detect overlap */
	UFUNCTION()
	virtual void OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
