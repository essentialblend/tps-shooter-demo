
#include "BTTaskNode_ShootTask.h"
#include "AIController.h"
#include "TPSProject/Characters/CharShooter.h"

UBTTaskNode_ShootTask::UBTTaskNode_ShootTask()
{
	NodeName = "FireTask";
}

EBTNodeResult::Type UBTTaskNode_ShootTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
	ACharShooter* AIChar = Cast<ACharShooter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AIChar == nullptr) return EBTNodeResult::Failed;
	AIChar->FireAt();
	return EBTNodeResult::Succeeded;
}
