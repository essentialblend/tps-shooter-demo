// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

class UBehaviorTree;

UCLASS()
class TPSPROJECT_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	bool IsDead() const;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere);
	UBehaviorTree* AIBTree;
	APawn* PlayerPawn = nullptr;
	
};
