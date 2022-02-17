// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CurrentLocation.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTService_CurrentLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:
	UBTService_CurrentLocation();
	
	protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
