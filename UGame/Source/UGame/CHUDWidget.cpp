#include "CHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Global.h"
//#include "ABCharacterStatComponent.h"
#include "CPlayerState.h"

//
//void UCHUDWidget::BindCharacterStat(UABCharacterStatComponent * CharacterStat)
//{
//	ABCHECK(nullptr != CharacterStat);
//	//CurrentCharacterStat = CharacterStat;
//	CharacterStat->OnHPChanged.AddUObject(this, &UCHUDWidget::UpdateCharacterStat);
//}

void UCHUDWidget::BindPlayerState(ACPlayerState * PlayerState)
{
	ABCHECK(nullptr != PlayerState);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UCHUDWidget::UpdatePlayerState);
}

void UCHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(nullptr != HPBar);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	ABCHECK(nullptr != ExpBar);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	ABCHECK(nullptr != PlayerName);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	ABCHECK(nullptr != PlayerLevel);

	CurrentAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentAmmo")));
	ABCHECK(nullptr != CurrentAmmo);

	CurrenMaxAmmo = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtMaxAmmo")));
	ABCHECK(nullptr != CurrenMaxAmmo);
}

void UCHUDWidget::UpdateCharacterStat()
{
	//ABCHECK(CurrentCharacterStat.IsValid());

	//HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());

}

void UCHUDWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());
	HPBar->SetPercent(CurrentPlayerState->GetPlayerHPRatio());
	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	//PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentAmmo->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCurrentAmmo())));
	CurrenMaxAmmo->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCurrentMaxAmmo())));
}