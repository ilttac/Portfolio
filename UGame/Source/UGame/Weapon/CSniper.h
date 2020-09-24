#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CSniper.generated.h"

UCLASS()
class UGAME_API ACSniper : public ACWeapon
{
	GENERATED_BODY()

public:
	ACSniper();

protected:
	virtual void BeginPlay() override;
	
};
