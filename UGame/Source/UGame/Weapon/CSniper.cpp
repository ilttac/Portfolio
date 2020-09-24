#include "CSniper.h"
#include "Global.h"

ACSniper::ACSniper()
{
	FString path = L"";
	
	path = L"SkeletalMesh'/Game/SciFiWeapLight/Weapons/White_SniperRifle.White_SniperRifle'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> sniper(*path);
	if (sniper.Succeeded())
		Mesh->SetSkeletalMesh(sniper.Object);

}

void ACSniper::BeginPlay()
{
	Super::BeginPlay();
}

