#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Attack_BuffBlue.generated.h"



UCLASS()
class UGAME_API UCBTTaskNode_Attack_BuffBlue : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float AttackDelay = 2.0f;

public:
	UCBTTaskNode_Attack_BuffBlue();
	
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float StartTime = 0.0f;
	bool bAttacking = false;
};
