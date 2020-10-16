#include "CBTTaskNode_Attack_BuffBlue.h"
#include "Global.h"
#include "Enemys/CBuffBlue.h"
#include "Enemys/CAIBuffBlueController.h"


UCBTTaskNode_Attack_BuffBlue::UCBTTaskNode_Attack_BuffBlue()
{
	bNotifyTick = true;

	NodeName = "Attack";
}

EBTNodeResult::Type UCBTTaskNode_Attack_BuffBlue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	//Buff_blue
	ACBuffBlue* buffBlue = Cast<ACBuffBlue>(OwnerComp.GetAIOwner()->GetPawn());
	RetNullResult(buffBlue, EBTNodeResult::Failed);

	bAttacking = true;
	buffBlue->BeginAttack();

	buffBlue->OnEndAttack.BindLambda([&]()
	{
		bAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack_BuffBlue::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	StartTime += DeltaSeconds;

	if (bAttacking == false && StartTime > AttackDelay)
	{
		StartTime = 0.0f;

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
