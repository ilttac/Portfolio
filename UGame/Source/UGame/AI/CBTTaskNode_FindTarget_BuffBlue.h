#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_FindTarget_BuffBlue.generated.h"

UCLASS()
class UGAME_API UCBTTaskNode_FindTarget_BuffBlue : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Distance = 1000;

public:
	UCBTTaskNode_FindTarget_BuffBlue();


private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
