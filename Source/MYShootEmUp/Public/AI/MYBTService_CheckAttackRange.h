// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MYBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTEMUP_API UMYBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category= "AI")
	FBlackboardKeySelector CanAttackKey;

	UPROPERTY(EditAnywhere, Category= "AI")
	FBlackboardKeySelector AttackRangeKey;
	
};