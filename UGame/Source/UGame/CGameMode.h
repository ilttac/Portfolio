#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Blue, Red,
};

UCLASS(minimalapi)
class ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();
};



