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

	path = L"Blueprint'/Game/Enemy/BP_CAIController.BP_CAIController_C'";
	ConstructorHelpers::FClassFinder<ACAIController> perception(*path);
	if (perception.Succeeded())
		AIControllerClass = perception.Class;

	path = L"AnimMontage'/Game/Character/Montages/Hit_Reaction_Montage.Hit_Reaction_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hittedMotage(*path);
	if (hittedMotage.Succeeded())
		HittedMontage = hittedMotage.Object;
	
	path = L"AnimMontage'/Game/Character/Montages/GetHitBackFall_Montage.GetHitBackFall_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> deadMontage(*path);
	if (deadMontage.Succeeded())
		DeadMontage = deadMontage.Object;

	path = L"AnimMontage'/Game/Character/Montages/Armed_Attack_Montage.Armed_Attack_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attackMontage(*path);
	if (attackMontage.Succeeded())
		AttackMontage = attackMontage.Object;

	path = L"ParticleSystem'/Game/Character/Particles/PS_Blood_Splatter.PS_Blood_Splatter'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(*path);
	if (particle.Succeeded())
		Particle = particle.Object;

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


}


void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString text = L"";
	text.Append(GetName());
	text.Append(":");
	text.Append(FString::FromInt((int)GetActorLocation().X));
	text.Append(",");
	text.Append(FString::FromInt((int)GetActorLocation().Y));
	Text->SetText(text);
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
		PlayAnimMontage(HittedMontage, 3.0);

		FVector direction = GetActorForwardVector().GetSafeNormal();
		direction *= GetCharacterMovement()->Mass * -5.0f;

		LaunchCharacter(direction, true, false);
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

void ACEnemy::BeginAttack()
{
	PlayAnimMontage(AttackMontage, 1.5f);
}

void ACEnemy::EndAttack()
{
	OnEndAttack.Execute();
}

void ACEnemy::Die()
{
	if (bDead == true) return;

	bDead = true;

	float rate = PlayAnimMontage(DeadMontage, 1.0f, "Start");

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ACEnemy::FinishDie, rate - 1.5f);
}

void ACEnemy::FinishDie()
{
	Destroy();
}