#include "CWeapon.h"
#include "Global.h"
#include "CPlayer.h"
#include "CWeaponSheet.h"

ACWeapon::ACWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(Mesh);

}

void ACWeapon::AttackAction()
{
	ACPlayer* player = ACPlayer::GetInstance();
	FAttachmentWeapon weapon = player->GetCurrentWeapon();


	UAnimMontage* montage = weapon.Montage;
	RetNull(montage);

	float playRate = weapon.PlayRate;
	player->PlayAnimMontage(montage, playRate);
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::OnBegin);
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACWeapon::OnBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Attack(OtherActor);
}

void ACWeapon::Attack(AActor * OtherActor)
{
	if (this == OtherActor)
	{
		return;
	}
	if (GetOwner() == OtherActor)
	{
		return;
	}

	UGameplayStatics::ApplyDamage(OtherActor, 20.0f, NULL, GetOwner(), NULL);
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
