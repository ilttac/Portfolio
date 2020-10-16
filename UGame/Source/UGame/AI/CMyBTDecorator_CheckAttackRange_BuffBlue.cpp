#include "CMyBTDecorator_CheckAttackRange_BuffBlue.h"
#include "Global.h"
#include "Enemys/CAIBuffBlueController.h"

UCMyBTDecorator_CheckAttackRange_BuffBlue::UCMyBTDecorator_CheckAttackRange_BuffBlue()
{
	NodeName = "Check Attack Range";
}

bool UCMyBTDecorator_CheckAttackRange_BuffBlue::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACAIBuffBlueController* controller = Cast<ACAIBuffBlueController>(OwnerComp.GetAIOwner());
	APawn* pawn = controller->GetPawn();

	UObject* trackerObj = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Tracker");
	APawn* target =  Cast<APawn>(trackerObj);
	RetNullResult(target, false);

	if (target->GetDistanceTo(pawn) <= Range)
		return true;

	return false;
}
