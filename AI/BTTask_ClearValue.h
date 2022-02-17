// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearValue.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTTask_ClearValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	UBTTask_ClearValue();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
