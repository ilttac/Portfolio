#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "CPerceptionAIController.generated.h"

UCLASS()
class UGAME_API ACPerceptionAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleDefaultsOnly)
		class UAISenseConfig_Sight* Sight;

	UPROPERTY(VisibleDefaultsOnly)
		class UAISenseConfig_Hearing* Hearing;

public:
	ACPerceptionAIController();

protected:
	void BeginPlay() override;


private:
	UFUNCTION()
		void OnSensingTarget(AActor* Actor, FAIStimulus Stimulus);

protected:
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;
	
};
