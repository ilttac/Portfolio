#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_FindTarget.generated.h"

UCLASS()
class U04_COMBAT_API UCBTTaskNode_FindTarget : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Distance = 1000;

public:
	UCBTTaskNode_FindTarget();


private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
