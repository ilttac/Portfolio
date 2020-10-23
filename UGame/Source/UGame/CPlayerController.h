#pragma once

#include "UGame.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerState.h"
#include "CPlayerController.generated.h"

UCLASS()
class UGAME_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	class UCHUDWidget* GetHUDWidget() const;
	//void NPCKill(class AABCharacter* KilledNPC) const;
	//void AddGameScore() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UCHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
		class UCHUDWidget* HUDWidget;

	static ACPlayerState* CPlayerState;
public:
	FORCEINLINE static ACPlayerState* GetPlayerStateInstnace() { return CPlayerState; }
};
