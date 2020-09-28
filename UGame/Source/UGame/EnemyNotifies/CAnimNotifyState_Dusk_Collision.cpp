#include "CAnimNotifyState_Dusk_Collision.h"
#include "Global.h"
#include "CEnemy.h"

void UCAnimNotifyState_Dusk_Collision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//RetNull(player);

	//player->GetCurrentWeapon().WeaponActor->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	if (enemy != NULL)
	{
		enemy->GetSwordCapsuleR()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		return;
	}

}

void UCAnimNotifyState_Dusk_Collision::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCAnimNotifyState_Dusk_Collision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//RetNull(player);

	//player->GetCurrentWeapon().WeaponActor->GetCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	if (enemy != NULL)
	{
		enemy->GetSwordCapsuleR()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
}
