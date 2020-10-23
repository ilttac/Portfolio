#pragma once

#include "UGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlayer.h"
#include "CBulletItemBox.generated.h"

UCLASS()
class UGAME_API ACBulletItemBox : public AActor
{
	GENERATED_BODY()

public:
	ACBulletItemBox();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* Effect;
private:
	UPROPERTY(EditInstanceOnly, Category = Box)
		TSubclassOf<class ACPlayerState> PlayerStateClass;

	UPROPERTY(EditDefaultsOnly, Category = Buleet)
		EAttachmentWeaponType WeaponType = EAttachmentWeaponType::Assault;
private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEffectFinished(class UParticleSystemComponent* PSystem);
};
