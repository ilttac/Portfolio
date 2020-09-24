#include "CPlayerState.h"


ACPlayerState::ACPlayerState()
{
	Health = 100.0f;
	Death = 0;
	Max_AssaultAmmo = 40;
	Max_SniperAmmo = 10;
	AssaultAmmo = Max_AssaultAmmo;
	SniperAmmo = Max_SniperAmmo;
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
		AssaultAmmo = Max_AssaultAmmo;
		CurrentAmmo = AssaultAmmo;
	}
	else if (type == EAttachmentWeaponType::Sniper)
	{
		SniperAmmo = Max_SniperAmmo;
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

void ACPlayerState::InitPlayerData()
{
}
//
//void ACPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
//{
//}
//