#include "CAIController.h"
#include  "Global.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

ACAIController::ACAIController()
{
	SetGenericTeamId(FGenericTeamId(1));

	FString path = L"";

	path = "BehaviorTree'/Game/Enemy/BT.BT'";
	ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;

	path = "BlackboardData'/Game/Enemy/BB.BB'";
	ConstructorHelpers::FObjectFinder<UBlackboardData> bb(*path);
	if (bb.Succeeded())
		BB = bb.Object;

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

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController::OnSensingTarget);
}

void ACAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BB, Blackboard))
		RunBehaviorTree(BT);

	SetActorLabel(InPawn->GetName() + L"Controller");
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::OnSensingTarget(AActor * Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject("Tracker", Actor);
		CLog::Log(Actor->GetName());
	}
	else
	{
		Blackboard->SetValueAsObject("Tracker", NULL);
		//CLog::Log("NULL");
	}
}
