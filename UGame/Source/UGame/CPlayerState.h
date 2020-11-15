#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CGameMode.h"
#include "CPlayer.h"
#include "CPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

UCLASS()
class UGAME_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACPlayerState();
	
public:
	UPROPERTY(EditDefaultsOnly)
		float MAX_Health;
	UPROPERTY(EditDefaultsOnly)
		float Health;
	UPROPERTY(EditDefaultsOnly)
		int AssaultAmmo;
	UPROPERTY(EditDefaultsOnly)
		int SniperAmmo;
	UPROPERTY(EditDefaultsOnly)
		int Max_AssaultAmmo;//³²Àº ÃÑ¾Ë°¹¼öÀÇ ÀÇ¹Ì
	UPROPERTY(EditDefaultsOnly)
		int Max_SniperAmmo;
	UPROPERTY(EditDefaultsOnly)
		int RelaodMaxAmmo_Assault;
	UPROPERTY(EditDefaultsOnly)
		int RelaodMaxAmmo_Sniper;
	UPROPERTY(EditDefaultsOnly)
		float Death;
	
private:
	UPROPERTY()
		int CurrentAmmo;
	UPROPERTY()
		int CurrentMaxAmmo;
public:

	int32 GetGameScore() const;
	int32 GetCharacterLevel() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	void AddGameScore();

	void AmmoReload(EAttachmentWeaponType type);

	void SubAmmo(EAttachmentWeaponType type);
	
	int GetAssaultAmmo() { return AssaultAmmo; }
	int GetSniperAmmo() { return SniperAmmo; }
	int GetCurrentAmmo() { return CurrentAmmo; }
	int GetCurrentMaxAmmo() { return CurrentMaxAmmo;	}
	float GetPlayerHPRatio();


	void PlayerTakeDamage(float damage);
	float GetPlayerHealth() { return Health; }

	void SetCurrentAmmo(EAttachmentWeaponType type);
	void SetMaxAmmo(EAttachmentWeaponType type,int count);
	void InitPlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
		int32 GameScore;

	UPROPERTY(Transient)
		int32 CharacterLevel;

	UPROPERTY(Transient)
		int32 Exp;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	//struct FABCharacterData* CurrentStatData;
};
