#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_FireNoise.generated.h"

UCLASS()
class UGAME_API UCAnimNotify_FireNoise : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class USoundWave* Cue;

public:
	UCAnimNotify_FireNoise();

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
