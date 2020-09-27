#include "CMyBTDecorator_CheckAttackRange.h"
#include "Global.h"
#include "CAIController.h"

UCMyBTDecorator_CheckAttackRange::UCMyBTDecorator_CheckAttackRange()
{
	NodeName = "Check Attack Range";
}

bool UCMyBTDecorator_CheckAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	APawn* pawn = controller->GetPawn();

	UObject* trackerObj = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Tracker");
	APawn* target =  Cast<APawn>(trackerObj);
	RetNullResult(target, false);

	if (target->GetDistanceTo(pawn) <= Range)
		return true;

	return false;
}
