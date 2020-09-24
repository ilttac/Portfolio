// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CGameInstance.h"
#include "Global.h"

UCGameInstance::UCGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/ABCharacterData.ABCharacterData");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
	ABCHECK(DT_ABCHARACTER.Succeeded());
	ABCharacterTable = DT_ABCHARACTER.Object;
	ABCHECK(ABCharacterTable->GetRowMap().Num() > 0);
}

void UCGameInstance::Init()
{
	Super::Init();
}

FABCharacterData* UCGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
}
