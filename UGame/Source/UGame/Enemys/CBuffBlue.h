#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBuffBlue.generated.h"

DECLARE_DELEGATE(FOnEndAttackDelegate);
DECLARE_DELEGATE(FOnEndMoveDelegate);
UCLASS()
class UGAME_API ACBuffBlue : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.0f;

private:
	UPROPERTY(VisibleInstanceOnly)
		class UParticleSystem* Particle;
	
	UPROPERTY(VisibleInstanceOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACBuffBlue_Bullet> BulletClass;
public:
	FOnEndAttackDelegate OnEndAttack;
	FOnEndMoveDelegate OnEndMove;

public:	
	ACBuffBlue();
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void BeginAttack();
	void EndAttack();
	
	void Patrol(FVector Dest,float Speed,float DeltaSeconds);

	void Fire();


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
private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
