#include "CPlayerController.h"
#include "Global.h"
#include "CHUDWidget.h"
#include "CPlayerState.h"


ACPlayerState* ACPlayerController::CPlayerState = NULL;

ACPlayerController::ACPlayerController()
{
	static ConstructorHelpers::FClassFinder<UCHUDWidget> UI_HUD_C(TEXT("WidgetBlueprint'/Game/UI/UI_HUD.UI_HUD_C'"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

void ACPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void ACPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	ABLOG_S(Warning);
}

UCHUDWidget* ACPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

//void ACPlayerController::NPCKill(AABCharacter * KilledNPC) const
//{
//}
//
//void ACPlayerController::AddGameScore() const
//{
//}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UCHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	CPlayerState = Cast<ACPlayerState>(PlayerState);
	ABCHECK(nullptr != CPlayerState);
	HUDWidget->BindPlayerState(CPlayerState);
	CPlayerState->OnPlayerStateChanged.Broadcast();
}
