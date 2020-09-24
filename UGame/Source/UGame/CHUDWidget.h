// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UGame.h"
#include "Blueprint/UserWidget.h"
#include "CHUDWidget.generated.h"

UCLASS()
class UGAME_API UCHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//void BindCharacterStat(class UABCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ACPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	//TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class ACPlayerState> CurrentPlayerState;

	UPROPERTY()
		class UProgressBar* HPBar;

	UPROPERTY()
		class UProgressBar* ExpBar;

	UPROPERTY()
		class UTextBlock* PlayerName;

	UPROPERTY()
		class UTextBlock* PlayerLevel;

	UPROPERTY()
		class UTextBlock* CurrentAmmo;

	UPROPERTY()
		class UTextBlock* CurrenMaxAmmo;
};
