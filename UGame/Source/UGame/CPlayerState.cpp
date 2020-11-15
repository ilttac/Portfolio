#include "CPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "CLog.h"


ACPlayerState::ACPlayerState()
{
	MAX_Health = 100.0f;
	Health = 100.0f;
	Death = 0;
	Max_AssaultAmmo = 40;
	Max_SniperAmmo = 10;
	AssaultAmmo = Max_AssaultAmmo;
	SniperAmmo = Max_SniperAmmo;
	RelaodMaxAmmo_Assault = 40;
	RelaodMaxAmmo_Sniper = 10;
	CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}

int32 ACPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ACPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

float ACPlayerState::GetExpRatio() const
{
	return 0.0f;
}

bool ACPlayerState::AddExp(int32 IncomeExp)
{
	//if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
	//	return 0.0f;

	//float Result = (float)Exp / (float)CurrentStatData->NextExp;
	//ABLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	//return Result;
	return false;
}

void ACPlayerState::AddGameScore()
{
}

void ACPlayerState::AmmoReload(EAttachmentWeaponType type)
{
	if (type == EAttachmentWeaponType::Assault)
	{
		AssaultAmmo = RelaodMaxAmmo_Assault;
		CurrentAmmo = AssaultAmmo;
	}
	else if (type == EAttachmentWeaponType::Sniper)
	{
		SniperAmmo = RelaodMaxAmmo_Sniper;
		CurrentAmmo = SniperAmmo;
	}
}

void ACPlayerState::SubAmmo(EAttachmentWeaponType type)
{
	CurrentAmmo--;

	if (type == EAttachmentWeaponType::Assault)
	{
		AssaultAmmo--;
	}
	else if (type == EAttachmentWeaponType::Sniper)
	{
		SniperAmmo--;
	}
}

float ACPlayerState::GetPlayerHPRatio()
{
	return (Health < KINDA_SMALL_NUMBER) ? 0.0f : (Health / MAX_Health);
}

void ACPlayerState::PlayerTakeDamage(float damage)
{
	Health = UKismetMathLibrary::Clamp(Health - damage, 0.0f, 100.0f);
	CLog::Log(Health);
	//set HUD ? hud UMG 업데이트 해야함
}

void ACPlayerState::SetCurrentAmmo(EAttachmentWeaponType type)
{
	if (type == EAttachmentWeaponType::Assault)
	{
		CurrentAmmo = AssaultAmmo;
		CurrentMaxAmmo = Max_AssaultAmmo;
		OnPlayerStateChanged.Broadcast();
	}
	else if(type == EAttachmentWeaponType::Sniper)
	{
		CurrentAmmo = SniperAmmo;
		CurrentMaxAmmo = Max_SniperAmmo;
		OnPlayerStateChanged.Broadcast();
	}
}

void ACPlayerState::SetMaxAmmo(EAttachmentWeaponType type,int count)
{
	if (type == EAttachmentWeaponType::Assault)
	{
		Max_AssaultAmmo += count;
		CurrentMaxAmmo = Max_AssaultAmmo;
		OnPlayerStateChanged.Broadcast();
	}
	else if (type == EAttachmentWeaponType::Sniper)
	{
		Max_SniperAmmo += count;
		CurrentMaxAmmo = Max_SniperAmmo;
		OnPlayerStateChanged.Broadcast();
	}
}

void ACPlayerState::InitPlayerData()
{
}
//
//void ACPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
//{
//}
//