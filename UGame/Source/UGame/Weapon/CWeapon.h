#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

UCLASS()
class UGAME_API ACWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
		float Power;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

public:
	ACWeapon();

	FORCEINLINE class UCapsuleComponent* GetCapsule() { return Capsule; }
	FORCEINLINE class USkeletalMeshComponent* GetMeshComp() { return Mesh; }

	UFUNCTION()
		virtual void AttackAction();
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	virtual void Attack(AActor* OtherActor);
};
