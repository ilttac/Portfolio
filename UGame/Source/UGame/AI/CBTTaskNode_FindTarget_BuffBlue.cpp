#include "CBTTaskNode_FindTarget_BuffBlue.h"
#include "Global.h"
#include "Enemys/CAIBuffBlueController.h"
#include "NavigationSystem.h"

UCBTTaskNode_FindTarget_BuffBlue::UCBTTaskNode_FindTarget_BuffBlue()
{
	NodeName = "Find Target";
}

EBTNodeResult::Type UCBTTaskNode_FindTarget_BuffBlue::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type type =  Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIBuffBlueController* controller = Cast<ACAIBuffBlueController>(OwnerComp.GetAIOwner());
	APawn* pawn = controller->GetPawn();
	//ACharacter* character = controller->GetCharacter();

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	verifyf(navSystem != nullptr, L"navSystem == nullptr");
	//controller->MoveToLocation();
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
	location.Location.Z = pawn->GetActorLocation().Z + 300;
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("Target", location.Location);

	return EBTNodeResult::Succeeded;
}
