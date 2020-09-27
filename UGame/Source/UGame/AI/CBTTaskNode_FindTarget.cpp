#include "CBTTaskNode_FindTarget.h"
#include "Global.h"
#include "CAIController.h"
#include "NavigationSystem.h"

UCBTTaskNode_FindTarget::UCBTTaskNode_FindTarget()
{
	NodeName = "Find Target";

}

EBTNodeResult::Type UCBTTaskNode_FindTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type type =  Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	APawn* pawn = controller->GetPawn();

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	verifyf(navSystem != nullptr, L"navSystem == nullptr");

	FNavLocation location;
	bool b = false;
	do
	{
		b = navSystem->GetRandomPointInNavigableRadius
		(
			pawn->GetActorLocation(),
			Distance,
			location
		);
	} while (b == false);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("Target", location.Location);

	return EBTNodeResult::Succeeded;
}
