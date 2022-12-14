// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickUp.h"

#include "Components/SphereComponent.h"

// Sets default values
ABasePickUp::ABasePickUp() :
	PickUpLifeSpan(8.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PickupMesh;

	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnSphereColliderBeginOverlap);

}

void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(PickUpLifeSpan);
}

void ABasePickUp::OnPicked(AMYCharacterBase* OverlappedCharacter)
{
	SphereCollider->SetActive(false);
	Destroy();
}

void ABasePickUp::OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor || OtherComp->ComponentHasTag(FName("Leader")) == false) return;	
	
	if (AMYCharacterBase* Char = Cast<AMYCharacterBase>(OtherActor))
	{
		OnPicked(Char);
	}
}


