#include "CAssaultRifle.h"
#include "Global.h"

ACAssaultRifle::ACAssaultRifle()
{
	FString path = L"";
	
	path = L"SkeletalMesh'/Game/SciFiWeapLight/Weapons/White_AssaultRifle.White_AssaultRifle'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> assaultRifle(*path);
	if (assaultRifle.Succeeded())
		Mesh->SetSkeletalMesh(assaultRifle.Object);

}

void ACAssaultRifle::BeginPlay()
{
	Super::BeginPlay();
}