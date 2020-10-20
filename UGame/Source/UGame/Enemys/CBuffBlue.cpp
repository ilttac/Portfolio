#include "CBuffBlue.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CMoveAIController.h"
#include "CPerceptionAIController.h"
#include "Enemys/CAIBuffBlueController.h"
#include "CPlayer.h"
#include "../Enemys/Bullets/CBuffBlue_Bullet.h"

ACBuffBlue::ACBuffBlue()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	FString path = L"";

	path = L"Blueprint'/Game/Enemy/EBuff_Blue/BP_CAIBuffBlueController.BP_CAIBuffBlueController_C'";
	ConstructorHelpers::FClassFinder<ACAIBuffBlueController> perception(*path);
	if (perception.Succeeded())
		AIControllerClass = perception.Class;

	path = L"AnimMontage'/Game/Enemy/ParagonMinions/Characters/Buff/Buff_Blue/Animations/Hitreat_Fwd_Montage.Hitreat_Fwd_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hittedMotage(*path);
	if (hittedMotage.Succeeded())
		HittedMontage = hittedMotage.Object;

	path = L"AnimMontage'/Game/Enemy/ParagonMinions/Characters/Buff/Buff_Blue/Animations/Death_Fwd_Montage.Death_Fwd_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> deadMontage(*path);
	if (deadMontage.Succeeded())
		DeadMontage = deadMontage.Object;

	path = L"AnimMontage'/Game/Enemy/ParagonMinions/Characters/Buff/Buff_Blue/Animations/Fire_Montage.Fire_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attackMontage(*path);
	if (attackMontage.Succeeded())
		AttackMontage = attackMontage.Object;

	path = L"ParticleSystem'/Game/Enemy/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Death/P_RangedMinion_Chunks3.P_RangedMinion_Chunks3'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(*path);
	if (particle.Succeeded())
		Particle = particle.Object;

	path = L"Blueprint'/Game/Enemy/EBuff_Blue/BP_CBuffBlue_Bullet.BP_CBuffBlue_Bullet_C'";
	ConstructorHelpers::FClassFinder<ACBuffBlue_Bullet> bullet(*path);
	if (bullet.Succeeded())
		BulletClass = bullet.Class;

	FString text = "";
	CreateTextRender(GetCapsuleComponent(), text, 100);
}

void ACBuffBlue::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

}


void ACBuffBlue::Tick(float DeltaTime)
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

float ACBuffBlue::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
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
void ACBuffBlue::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	UGameplayStatics::ApplyDamage(OtherActor, 20.0f, NULL, GetOwner(), NULL);

}
void ACBuffBlue::Fire()
{
	FVector	playerLocation = ACPlayer::GetInstance()->GetActorLocation();

	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation()
		, playerLocation);

	FVector location = GetMesh()->GetSocketLocation("MuzzleSocket");

	SetActorRotation(rotator);

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	if (BulletClass != NULL)
	{
		GetWorld()->SpawnActor<ACBuffBlue_Bullet>(BulletClass, location, rotator, params);
	}
}

void ACBuffBlue::BeginAttack()
{
	Fire();
	PlayAnimMontage(AttackMontage);
}

void ACBuffBlue::EndAttack()
{
	OnEndAttack.Execute();
}



void ACBuffBlue::Die()
{
	if (bDead == true) return;

	bDead = true;
	float rate = PlayAnimMontage(DeadMontage, 1.0f);
	FTimerHandle timer;
	auto aiController = Cast<ACAIBuffBlueController>(GetController());
	aiController->StopAI();
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ACBuffBlue::FinishDie, rate - 0.5f);
}

void ACBuffBlue::FinishDie()
{
	Destroy();
}