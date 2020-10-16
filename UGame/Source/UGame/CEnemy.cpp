#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CMoveAIController.h"
#include "CPerceptionAIController.h"
#include "CAIController.h"


ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	FString path = L"";

	path = L"Blueprint'/Game/Enemy/BP_CAIController2.BP_CAIController2_C'";
	ConstructorHelpers::FClassFinder<ACAIController> perception(*path);
	if (perception.Succeeded())
		AIControllerClass = perception.Class;

	path = L"AnimMontage'/Game/Enemy/Dusk_HitFornt_Montage.Dusk_HitFornt_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hittedMotage(*path);
	if (hittedMotage.Succeeded())
		HittedMontage = hittedMotage.Object;
	
	path = L"AnimMontage'/Game/Enemy/Dusk_Death_A_Montage.Dusk_Death_A_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> deadMontage(*path);
	if (deadMontage.Succeeded())
		DeadMontage = deadMontage.Object;

	path = L"AnimMontage'/Game/Enemy/Dusk_Attack_Montage01.Dusk_Attack_Montage01'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attackMontage(*path);
	if (attackMontage.Succeeded())
		AttackMontage = attackMontage.Object;

	path = L"ParticleSystem'/Game/Enemy/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Death/P_RangedMinion_Chunks3.P_RangedMinion_Chunks3'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(*path);
	if (particle.Succeeded())
		Particle = particle.Object;

	SwordCapsuleR = CreateDefaultSubobject<UCapsuleComponent>("WeaponCapsule");

	FString text = "";
	CreateTextRender(GetCapsuleComponent(), text, 100);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	SwordCapsuleR->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "Sword_R");
	SwordCapsuleR->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnBeginOverlap);
	SwordCapsuleR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString text = L"";
	text.Append(GetName());
	text.Append(L":");
	text.Append(FString::FromInt((int)GetActorLocation().X));
	text.Append(L",");
	text.Append(FString::FromInt((int)GetActorLocation().Y));
	Text->SetText(FText::FromString(text));
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float damage =  Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Health -= damage;
	AActor* attacker = DamageCauser;

	if (Health <= 0.0f)
	{
		Die();
		return damage;
	}

	///CLog::Print(Health);

	//LookAt
	{
		FVector loc = GetActorLocation();
		FVector attackLoc = attacker->GetActorLocation();

		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(loc, attackLoc);
		SetActorRotation(rotator);
	}

	//HitBack
	{
		//GetMesh()->PlayAnimation(Cast<UAnimationAsset>(HittedMontage), false);
		PlayAnimMontage(HittedMontage, 1.0);
		
		//FVector direction = GetActorForwardVector().GetSafeNormal();
		//direction *= GetCharacterMovement()->Mass * -5.0f;

		//LaunchCharacter(direction, true, false);
	}

	//HitEffect
	{
		UGameplayStatics::SpawnEmitterAttached
		(
			Particle, GetMesh(), "head", FVector(0, 0, 0), FRotator(0, 0, 0),
			EAttachLocation::KeepRelativeOffset
		);
		
	}

	

	return damage;
}
void ACEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	UGameplayStatics::ApplyDamage(OtherActor, 20.0f, NULL, GetOwner(), NULL);
	SwordCapsuleR->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}
void ACEnemy::BeginAttack()
{
	PlayAnimMontage(AttackMontage);
}

void ACEnemy::EndAttack()
{
	OnEndAttack.Execute();
}

void ACEnemy::Die()
{
	if (bDead == true) return;

	bDead = true;
	float rate = PlayAnimMontage(DeadMontage, 1.0f);
	FTimerHandle timer;
	auto aiController = Cast<ACAIController>(GetController());
	aiController->StopAI();
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ACEnemy::FinishDie, rate-0.5f);
}

void ACEnemy::FinishDie()
{
	Destroy();
}