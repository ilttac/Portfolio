#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CAssaultRifle.generated.h"

UCLASS()
class UGAME_API ACAssaultRifle : public ACWeapon
{
	GENERATED_BODY()

public:
	ACAssaultRifle();

protected:
	virtual void BeginPlay() override;
	
};
