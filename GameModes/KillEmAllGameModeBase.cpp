// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "TPSProject/AI/AIControllerBase.h"
#include "TPSProject/Controllers/ShooterPlayerController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp, Warning, TEXT(" KEA : Overriden."));

	APlayerController* PlayerContr = Cast<APlayerController>(PawnKilled->GetController());
	if(PlayerContr != nullptr)
	{
		EndGame(false);
	}

	for(AAIControllerBase* AIController : TActorRange<AAIControllerBase>(GetWorld()))
	{
		if(!AIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner) const
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
