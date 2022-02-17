// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ShootTask.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTTaskNode_ShootTask : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTaskNode_ShootTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
