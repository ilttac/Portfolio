#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBuffBlue_Bullet.generated.h"

UCLASS()
class UGAME_API ACBuffBlue_Bullet : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Collision;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* TrailParticle;


public:	
	ACBuffBlue_Bullet();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void SetProjectileVelocity(FVector SrcVec);
protected:
	virtual void BeginPlay() override;


};
