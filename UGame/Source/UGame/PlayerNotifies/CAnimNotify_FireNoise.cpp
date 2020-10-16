#include "CAnimNotify_FireNoise.h"
#include "Global.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"
#include "CPlayer.h"

UCAnimNotify_FireNoise::UCAnimNotify_FireNoise()
{
	FString path = L"SoundWave'/Game/SciFiWeapLight/Sound/Rifle/Wavs/Rifle_FireEnd01.Rifle_FireEnd01'";

	ConstructorHelpers::FObjectFinder<USoundWave> cue(*path);
	if (cue.Succeeded())
		Cue = cue.Object;

}

void UCAnimNotify_FireNoise::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* player = ACPlayer::GetInstance();

	if (Cue != NULL)
	{
		if (player != NULL)
		{
			//UGameplayStatics::PlaySoundAtLocation(player->GetWorld(), Cue, player->GetActorLocation());

			player->EmitNoise(1.0f);
		}
	}

	
	
}
