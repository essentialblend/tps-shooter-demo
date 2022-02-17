// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSProject/TPSProjectGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API AKillEmAllGameModeBase : public ATPSProjectGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner) const;
	
};
