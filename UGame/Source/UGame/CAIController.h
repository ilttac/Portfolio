#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "CAIController.generated.h"

UCLASS()
class UGAME_API ACAIController : public AAIController
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
	ACAIController();

protected:
	void BeginPlay() override;
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

private:
	UFUNCTION()
		void OnSensingTarget(AActor* Actor, FAIStimulus Stimulus);

private:
	class UBehaviorTree* BT;
	class UBlackboardData* BB;
	
};