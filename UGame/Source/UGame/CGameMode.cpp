#include "CGameMode.h"
#include "UGameHUD.h"
#include "CPlayer.h"
#include "CPlayerController.h"
#include "CPlayerState.h"
#include "UObject/ConstructorHelpers.h"

ACGameMode::ACGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(L"Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	if (PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
		PlayerControllerClass = ACPlayerController::StaticClass();
		PlayerStateClass = ACPlayerState::StaticClass();
	}

	HUDClass = AUGameHUD::StaticClass();
}
	