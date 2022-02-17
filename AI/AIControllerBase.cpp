
#include "AIControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSProject/Characters/CharShooter.h"


void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(AIBTree != nullptr)
	{
		RunBehaviorTree(AIBTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyStartLocation"), GetPawn()->GetActorLocation());
	}
}

bool AAIControllerBase::IsDead() const
{
	ACharShooter* ControlledCharacter = Cast<ACharShooter>(GetPawn());
	if(ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsCharDead();
	}
	return true;
}
