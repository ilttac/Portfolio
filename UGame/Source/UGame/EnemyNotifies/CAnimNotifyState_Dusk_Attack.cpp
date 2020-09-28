#include "CAnimNotifyState_Dusk_Attack.h"
#include "Global.h"
#include "CEnemy.h"

void UCAnimNotifyState_Dusk_Attack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//RetNull(player);
	//player->BeginAttack();
}

void UCAnimNotifyState_Dusk_Attack::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCAnimNotifyState_Dusk_Attack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());

	////FGenericTeamId teamID = player->GetGenericTeamId();

	//if (player != NULL)
	//{
	//	player->EndAttack();

	//	return;
	//}

	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	if (enemy != NULL)
	{
		enemy->EndAttack();
		return;
	}

}