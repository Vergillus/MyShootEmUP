// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickUp.h"

#include "Components/SphereComponent.h"

// Sets default values
ABasePickUp::ABasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PickupMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnSphereColliderBeginOverlap);

}

void ABasePickUp::OnPicked()
{
	SphereCollider->SetActive(false);
}

void ABasePickUp::OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


