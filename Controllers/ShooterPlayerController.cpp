// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MainWidget = CreateWidget(this, MainHUDClass, TEXT("Main HUD Widget"));
	MainWidget->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	MainWidget->RemoveFromParent();
	if(bIsWinner)
	{
		UUserWidget* WinWidget = CreateWidget(this,WinScreenClass, TEXT("Win Screen Widget"));
		if(WinWidget == nullptr) return;
		WinWidget->AddToViewport();
	}
	else
	{
		UUserWidget* LoseWidget = CreateWidget(this,LoseScreenClass, TEXT("Lose Screen Widget"));
		if(LoseWidget == nullptr) return;
		LoseWidget->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

