#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

DECLARE_DELEGATE(FOnEndAttackDelegate);

UCLASS()
class UGAME_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.0f;

private:
	UPROPERTY(VisibleInstanceOnly)
		class UParticleSystem* Particle;
	
	/*UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class UCameraShake> CameraShake;*/

	UPROPERTY(VisibleInstanceOnly)
		class UTextRenderComponent* Text;

public:
	FOnEndAttackDelegate OnEndAttack;
	
public:	
	ACEnemy();
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
 
	void BeginAttack();
	void EndAttack();

protected:
	virtual void BeginPlay() override;

private:
	void Die();
	void FinishDie();

private:
	class UAnimMontage* HittedMontage;
	class UAnimMontage* DeadMontage;
	class UAnimMontage* AttackMontage;

private:
	float Health;
	bool bDead;
};
