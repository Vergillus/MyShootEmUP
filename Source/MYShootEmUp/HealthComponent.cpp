// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent():
	MaxHealth(100),
	CurrentHealth(MaxHealth)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::DamageHealth(AActor* Instigator,float Damage)
{
	if(Damage <= 0) return;

	CurrentHealth -= Damage;
	CurrentHealth = FMath::Clamp(CurrentHealth,0,MaxHealth);

	OnReceiveHit.Broadcast(Instigator,MaxHealth,CurrentHealth);
	
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();		
	}
}


