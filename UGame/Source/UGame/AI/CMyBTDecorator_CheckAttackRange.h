#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CMyBTDecorator_CheckAttackRange.generated.h"

UCLASS()
class U04_COMBAT_API UCMyBTDecorator_CheckAttackRange : public UBTDecorator
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Range = 200.0f;

public:
	UCMyBTDecorator_CheckAttackRange();

protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
