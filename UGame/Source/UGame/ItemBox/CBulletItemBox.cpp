
#include "CBulletItemBox.h"
#include "Global.h"

#include "CPlayerState.h"
#include "CPlayerController.h"

// Sets default values
ACBulletItemBox::ACBulletItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;



	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);


	FString path = L"";

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	path = L"StaticMesh'/Game/SciFiWeapLight/Pickups/White_GrenadeLauncher_Pickup.White_GrenadeLauncher_Pickup'";
	static ConstructorHelpers::FObjectFinder<UStaticMesh> box(*path);

	if (box.Succeeded())
	{
		Box->SetStaticMesh(box.Object);
	}
	path = L"ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/P_AuraCircle_Ice_StartUp_01.P_AuraCircle_Ice_StartUp_01'";

	static ConstructorHelpers::FObjectFinder<UParticleSystem> effect(*path);

	if (effect.Succeeded())
	{
		Effect->SetTemplate(effect.Object);
		Effect->bAutoActivate = false;
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	//Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	

}

void ACBulletItemBox::BeginPlay()
{
	Super::BeginPlay();
	Effect->Activate(true);
}

void ACBulletItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACBulletItemBox::OnCharacterOverlap);
}

void ACBulletItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABLOG_S(Warning);
	auto PlayerCharacter = Cast<ACPlayer>(OtherActor);
	ABCHECK(nullptr != PlayerCharacter);
	PlayerStateClass = ACPlayerState::StaticClass();
	if (nullptr != PlayerCharacter && nullptr!= PlayerStateClass )
	{
		Box->SetHiddenInGame(true, true);
		SetActorEnableCollision(false);
		
		ACPlayerState* playerState = ACPlayerController::GetPlayerStateInstnace();
		ABCHECK(nullptr != playerState);
		playerState->SetMaxAmmo(WeaponType, 40);
		playerState->OnPlayerStateChanged.Broadcast();
		Effect->Activate(false);
		Destroy();
	}
	else
	{
		ABLOG(Warning, TEXT("%s please Set PlayerCharacter AND PlyaerState : PlayerCharacter is nullptr OR playerstate is null"), *PlayerCharacter->GetName());
	}
}

void ACBulletItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	
	Destroy();
}
