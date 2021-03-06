#pragma once

#include "UGame.h"
#include "GameFramework/Character.h"
#include "CGameMode.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

DECLARE_DELEGATE(FAttachDelegate);

UENUM(BlueprintType)
enum class EAttachmentWeaponType : uint8
{
	Assault = 0,
	Sniper,
	Count
};

USTRUCT(BlueprintType)
struct FAttachmentWeapon
{
	GENERATED_USTRUCT_BODY()

public:
	FName Socket = "";
	UClass* WeaponClass = NULL;
	class ACWeapon* WeaponActor = NULL;
	float Power = 0.0f;
	float PlayRate = 1.0f;
	FAttachDelegate AttackDelegate;
};

UCLASS()
class UGAME_API ACPlayer : public ACharacter ,public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		float ZoomSpeed = 20.0f;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USceneComponent* Muzzle;

	UPROPERTY(VisibleDefaultsOnly)
		class UPawnNoiseEmitterComponent* NoiseEmitter;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem* MuzzleParticle;

	UPROPERTY(VisibleDefaultsOnly)
		class UAnimMontage* FireMontage;

	UPROPERTY(VisibleDefaultsOnly)
		class UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
		FVector GunOffset = FVector(100, 0, 0);

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* HitParticle;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USoundWave* ReloadSound;

	UPROPERTY(VisibleDefaultsOnly)
		class USoundWave* CastSound;


public:
	ACPlayer();

	FORCEINLINE bool GetDrawing() { return bDrawing; }
	FORCEINLINE bool GetSheathing() { return bSheathing; }
private:
	FGenericTeamId TeamId;
public:

	virtual FGenericTeamId GetGenericTeamId() const override{ return FGenericTeamId(0); }

	FORCEINLINE EAttachmentWeaponType GetCurrentWeaponType() { return CurrentWeapon; }
	FORCEINLINE FAttachmentWeapon GetCurrentWeapon() { return AttachmentWeapon[(int)CurrentWeapon]; }
	FORCEINLINE static ACPlayer* GetInstance() { return playerInstnace; }


	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnZoom(float Axis);

	void OnRunning();
	void OffRunning();
	void OnJumping();

	void OnAssult();
	void OnSniper();
	void OnReload();

	void OnSword();
	void OnFire();
	void StartFire();
	void StopFire();
	void Die();
	void OnBowAiming();

private:
	void BeginEquip(EAttachmentWeaponType Type);
	void EquipWeapon();

public:
	void EquippedWeapon();
	void GrapWeapon();

private:
	void SheathWeapon();

public:
	void SheatedWeapon();
	void UngrapWeapon();

public:
	void BeginAttack();
	void EndAttack();

public:
	void EmitNoise(float Volume);

private:
	TSubclassOf<class UAnimInstance> AnimInstanceClass;

private:
	bool bCanMove = true;

	bool bDrawn;
	bool bDrawing;
	bool bSheathing;
	bool bAttacking;
	bool bIsFiring = false;

	class UCWeaponSheet* WeaponSheet;
	EAttachmentWeaponType CurrentWeapon;
	FAttachmentWeapon AttachmentWeapon[(int)EAttachmentWeaponType::Count];

private:
	static ACPlayer* playerInstnace;
	FTimerHandle _timer;
};
//UCLASS()
//class UGAME_API //ACPlayer : public ACharacter
//{
//	GENERATED_BODY()
//
//public:
//	ACPlayer();
//
//	virtual void Tick(float DeltaTime) override;
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//private:
//	UPROPERTY(EditAnywhere, Category = "Camera")
//		float ZoomSpeed = 20.0f;
//
//private:
//	UPROPERTY(VisibleDefaultsOnly)
//		class USpringArmComponent* SpringArm;
//
//	UPROPERTY(VisibleDefaultsOnly)
//		class UCameraComponent* Camera;
//
//
//
//protected:
//	virtual void BeginPlay() override;
//	
//private:
//	static ACPlayer* playerInstnace;
//
//};
