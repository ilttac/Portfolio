#include "CBTTaskNode_Moveto_BuffBlue.h"
#include "Global.h"
#include "Enemys/CAIBuffBlueController.h"
#include "Enemys/CBuffBlue.h"
#include "NavigationSystem.h"


UCBTTaskNode_Moveto_BuffBlue::UCBTTaskNode_Moveto_BuffBlue()
{
	bNotifyTick = true;
	NodeName = "Move to BuffBlue";
}

EBTNodeResult::Type UCBTTaskNode_Moveto_BuffBlue::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type type =  Super::ExecuteTask(OwnerComp, NodeMemory);

	enemy = Cast<ACBuffBlue>(OwnerComp.GetAIOwner()->GetPawn());
	RetNullResult(enemy, EBTNodeResult::Failed);
	dest = OwnerComp.GetBlackboardComponent()->GetValueAsVector("Target");
	bisMoving = true;

	enemy->OnEndAttack.BindLambda([&]()
		{
			bisMoving = false;
		});


	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Moveto_BuffBlue::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (false == bisMoving)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		enemy->Patrol(dest, Speed, DeltaSeconds);
	}
	//StartTime += DeltaSeconds;

	//if (bAttacking == false && StartTime > AttackDelay)
	//{
	//	StartTime = 0.0f;

	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}

}
