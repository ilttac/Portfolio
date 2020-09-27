#include "CMoveAIController.h"
#include "Global.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ACMoveAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	FTimerManager& timer = GetWorld()->GetTimerManager();

	timer.SetTimer(RepeatTimeHandle, this, &ACMoveAIController::OnRepeat, RepeatInterval, true, 0.0f);
}

void ACMoveAIController::OnUnPossess()
{
	Super::OnUnPossess();

	FTimerManager& timer = GetWorld()->GetTimerManager();
	timer.ClearTimer(RepeatTimeHandle);
}

void ACMoveAIController::OnRepeat()
{
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	verifyf(navSystem != nullptr, L"nav != nullptr");

	FNavLocation location;
	bool b = false;

	do
	{
		b = navSystem->GetRandomPointInNavigableRadius
		(
			GetPawn()->GetActorLocation(),
			2000.0f,
			location
		);
	} while (b == false);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, location);
}
