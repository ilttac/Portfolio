#include "CPerceptionAIController.h"
#include "Global.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ACPerceptionAIController::ACPerceptionAIController()
{
	SetGenericTeamId(FGenericTeamId(1));

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 500.0f;
	Sight->LoseSightRadius = 600.0f;
	Sight->PeripheralVisionAngleDegrees = 45.0f;
	Sight->SetMaxAge(5.0f);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing");
	Hearing->HearingRange = 1000.0;
	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = false;
	Hearing->DetectionByAffiliation.bDetectNeutrals = false;
	Perception->ConfigureSense(*Hearing);
}

void ACPerceptionAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ACPerceptionAIController::OnSensingTarget);
}

void ACPerceptionAIController::OnSensingTarget(AActor * Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(this, Actor);
	}
}

void ACPerceptionAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACPerceptionAIController::OnUnPossess()
{
	Super::OnUnPossess();
}