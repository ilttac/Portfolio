#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CMyBTDecorator_CheckAttackRange_BuffBlue.generated.h"

UCLASS()
class UGAME_API UCMyBTDecorator_CheckAttackRange_BuffBlue : public UBTDecorator
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Range = 200.0f;

public:
	UCMyBTDecorator_CheckAttackRange_BuffBlue();

protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
