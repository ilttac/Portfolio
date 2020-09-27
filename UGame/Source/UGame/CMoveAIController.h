#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CMoveAIController.generated.h"

UCLASS()
class UGAME_API ACMoveAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float RepeatInterval = 3.0f;

protected:
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

private:
	UFUNCTION()
		void OnRepeat();

private:
	FTimerHandle RepeatTimeHandle;
	
};
