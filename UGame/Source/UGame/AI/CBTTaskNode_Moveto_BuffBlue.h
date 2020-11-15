#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Moveto_BuffBlue.generated.h"

UCLASS()
class UGAME_API UCBTTaskNode_Moveto_BuffBlue : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Speed = 3.0f;

private:
	FVector dest= FVector(0,0,0);
	bool bisMoving = false;
	class ACBuffBlue* enemy ;
public:
	UCBTTaskNode_Moveto_BuffBlue();


private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
