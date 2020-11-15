#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "CEnemy.h"
#include "CAIController.h"


UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	bNotifyTick = true;

	NodeName = "Attack";
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Dusk
	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	RetNullResult(enemy, EBTNodeResult::Failed);

	bAttacking = true;
	enemy->BeginAttack();

	enemy->OnEndAttack.BindLambda([&]()
		{
			bAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	StartTime += DeltaSeconds;

	if (bAttacking == false && StartTime > AttackDelay)
	{
		StartTime = 0.0f;

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
