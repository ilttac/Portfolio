#include "CPlayer.h"
#include "Global.h"
#include "CPlayerState.h"
#include "Weapon/CWeaponSheet.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/DamageType.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CAnimInstance.h"
#include "Weapon/CWeapon.h"
#include "Weapon/CBullet.h"
#include "CPlayerController.h"
ACPlayer* ACPlayer::playerInstnace = NULL;

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(GetMesh());

	////SpringArm->RelativeLocation = FVector(0, 0, 140);
	////SpringArm->RelativeRotation = FRotator(0, 90, 0);
	//SpringArm->TargetArmLength = 280.0f;
	//SpringArm->bUsePawnControlRotation = true;
	//SpringArm->bEnableCameraLag = true;
	//SpringArm->CameraLagSpeed = 20.0f;
	//SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(GetMesh());
	
	//Camera->RelativeLocation = FVector(-16, 80, 33);
	//Camera->RelativeRotation = FRotator(-10, 0, 0);
	//

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>("Gun");
	Gun->SetupAttachment(RootComponent);
	Gun->bCastDynamicShadow = false;
	Gun->CastShadow = false;

	Muzzle = CreateDefaultSubobject<USceneComponent>("Muzzle");
	Muzzle->SetupAttachment(Gun);
	Muzzle->SetRelativeLocation(FVector(0.2f, 48.5f, -10.5f));

	WeaponSheet = NewObject<UCWeaponSheet>();

	FString path = L"";
	for (int i = 0; i < WeaponSheet->GetRowCount(); ++i)
	{
		const FWeaponSheet* sheet = WeaponSheet->GetRowFromIndex(i);

		AttachmentWeapon[i].Socket = sheet->Socket;

		path = WeaponSheet->GetFullWeaponClassPath(sheet->Class);
		ConstructorHelpers::FClassFinder<ACWeapon> weapon(*path);

		if (weapon.Succeeded())
			AttachmentWeapon[i].WeaponClass = weapon.Class;

		AttachmentWeapon[i].Power = sheet->Power;
		AttachmentWeapon[i].PlayRate = sheet->PlayRate;

		path = WeaponSheet->GetFullMontagePath(sheet->Montage);
		ConstructorHelpers::FObjectFinder<UAnimMontage> animMontage(*path);

		if (animMontage.Succeeded()) 
			AttachmentWeapon[i].Montage = animMontage.Object;

		path = WeaponSheet->GetFullAnimInstancePath(sheet->AnimInstance);
		ConstructorHelpers::FClassFinder<UCAnimInstance> animInstance(*path);

		if (animInstance.Succeeded())
			AttachmentWeapon[i].AnimInstance = animInstance.Class;
	}

	path = L"ParticleSystem'/Game/SciFiWeapLight/FX/Particles/P_Pistol_MuzzleFlash_Dark.P_Pistol_MuzzleFlash_Dark'";

	ConstructorHelpers::FObjectFinder<UParticleSystem> muzzleParticle(*path);
	if (muzzleParticle.Succeeded())
		MuzzleParticle = muzzleParticle.Object;

	
	//NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>("NoiseEmitter");
	path = "AnimMontage'/Game/ParagonLtBelica/Characters/Heroes/Belica/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'";

	ConstructorHelpers::FObjectFinder<UAnimMontage> fire(*path);
	if (fire.Succeeded())
		FireMontage = fire.Object;

	path = L"Blueprint'/Game/Weapon/BP_CBullet.BP_CBullet_C'";;
	ConstructorHelpers::FClassFinder<ACBullet> bullet(*path);
	if (bullet.Succeeded())
		BulletClass = bullet.Class;

	path = L"ParticleSystem'/Game/SciFiWeapLight/FX/Particles/P_Impact_Metal_Large_Light.P_Impact_Metal_Large_Light'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> hitParticle(*path);
	if (hitParticle.Succeeded())
		HitParticle = hitParticle.Object;

	playerInstnace = this;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "head_1");
	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	for (FAttachmentWeapon& weapon : AttachmentWeapon)
	{
		if (weapon.WeaponClass != NULL)
		{
			weapon.WeaponActor = Cast<ACWeapon>(GetWorld()->SpawnActor(weapon.WeaponClass, &transform, params));
		}
	}
	CurrentWeapon = EAttachmentWeaponType::Assault;

	Gun->SetSkeletalMesh(AttachmentWeapon[(int)CurrentWeapon].WeaponActor->GetMeshComp()->SkeletalMesh);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), AttachmentWeapon[(int)CurrentWeapon].Socket);
	
	auto AACPlayerState = Cast<ACPlayerState>(GetPlayerState());
	ABCHECK(nullptr != AACPlayerState);
	AACPlayerState->SetCurrentAmmo(CurrentWeapon);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::OnMoveForward(float Axis)
{
	if (bCanMove == false)
	{
		return;
	}

	FRotator rotator = FRotator(0,GetControlRotation().Yaw, 0);
	FVector forward = FQuat(rotator).GetForwardVector();
	
	AddMovementInput(forward, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	if (bCanMove == false)
	{
		return;
	}

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector right = FQuat(rotator).GetRightVector();

	AddMovementInput(right, Axis);
}

void ACPlayer::OnTurn(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnLookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

//void ACPlayer::OnZoom(float Axis)
//{
//	SpringArm->TargetArmLength += (ZoomSpeed * Axis);
//	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 100.0f, 500.0f);
//}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ACPlayer::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void ACPlayer::OnJumping()
{
	if (bCanMove == false)
	{
		return;
	}
	Jump();
}

void ACPlayer::OnAssult()
{
	if (CurrentWeapon == EAttachmentWeaponType::Assault)
	{
		return;
	}
	BeginEquip(EAttachmentWeaponType::Assault);
}

void ACPlayer::OnSniper()
{
	if (CurrentWeapon == EAttachmentWeaponType::Sniper)
	{
		return;
	}
	BeginEquip(EAttachmentWeaponType::Sniper);
}
void ACPlayer::OnReload()
{
	auto AACPlayerState = Cast<ACPlayerState>(GetPlayerState());
	ABCHECK(nullptr != AACPlayerState);
	AACPlayerState->AmmoReload(CurrentWeapon);
	AACPlayerState->OnPlayerStateChanged.Broadcast();
}
void ACPlayer::OnFire()
{
	auto AACPlayerState = Cast<ACPlayerState>(GetPlayerState());
	ABCHECK(nullptr != AACPlayerState);
	if (AACPlayerState->GetCurrentAmmo() <= 0)
	{
		return;
	}
	if (bIsFiring)
	{
		float f;
		if (FireMontage != NULL)
		{
			UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

			if (animInstance != NULL)
				f = animInstance->Montage_Play(FireMontage, AttachmentWeapon[(int)CurrentWeapon].PlayRate)/ AttachmentWeapon[(int)CurrentWeapon].PlayRate +0.1f;
		}

		if (BulletClass != NULL)
		{
			FRotator rotator = GetControlRotation();
			FVector location = Muzzle->GetComponentLocation() + rotator.RotateVector(GunOffset);

			if (MuzzleParticle != NULL)
			{
				if (CurrentWeapon == EAttachmentWeaponType::Sniper)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticle, Muzzle->GetComponentLocation() + rotator.RotateVector(GunOffset));

				}
				else
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticle, Muzzle->GetComponentLocation());
				}
				AACPlayerState->SubAmmo(CurrentWeapon);
				AACPlayerState->OnPlayerStateChanged.Broadcast();

			}

			FQuat(Camera->GetComponentRotation()).GetForwardVector();//ī�޶� ����frontvector

			FVector start = Camera->GetComponentLocation();
			FVector end = Camera->GetComponentLocation() + FQuat(Camera->GetComponentRotation()).GetForwardVector() * 1000;//ī�޶� ����frontvector * 1000.0f;

			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 3);

			FCollisionQueryParams params1;
			params1.AddIgnoredActor(this);
			FHitResult hit;
			this->GetWorld()->LineTraceSingleByChannel
			(
				hit, start, end, ECollisionChannel::ECC_PhysicsBody, params1
			);
			FVector loc;
			FRotator rotator2;
			if (hit.GetActor() != NULL)
			{
				loc = hit.Location;
				rotator2 = UKismetMathLibrary::FindLookAtRotation(location, loc);

				if (HitParticle != NULL)
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, hit.Location);

			}
			else
			{
				rotator2 = UKismetMathLibrary::FindLookAtRotation(location, end);
			}

			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			GetWorld()->SpawnActor<ACBullet>(BulletClass, location, rotator2, params);
		}
		GetWorld()->GetTimerManager().SetTimer(_timer, this, &ACPlayer::OnFire, f, false);
	}
	
}

void ACPlayer::StartFire()
{
	bIsFiring = true;
	OnFire();
}

void ACPlayer::StopFire()
{
	bIsFiring = false;
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);
//	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::OffRunning);

	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &ACPlayer::OnJumping);
	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Assault", EInputEvent::IE_Pressed, this, &ACPlayer::OnAssult);
	PlayerInputComponent->BindAction("Sniper", EInputEvent::IE_Pressed, this, &ACPlayer::OnSniper);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::StopFire);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Released, this, &ACPlayer::OnReload);
}

void ACPlayer::BeginEquip(EAttachmentWeaponType Type)
{
	//Type Ȯ���� ���� �Լ����� üũ��.
	CurrentWeapon = Type;

	Gun->SetSkeletalMesh(AttachmentWeapon[(int)CurrentWeapon].WeaponActor->GetMeshComp()->SkeletalMesh);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), AttachmentWeapon[(int)CurrentWeapon].Socket);
	auto AACPlayerState = Cast<ACPlayerState>(GetPlayerState());
	ABCHECK(nullptr != AACPlayerState);
	AACPlayerState->SetCurrentAmmo(CurrentWeapon);
}

void ACPlayer::EquipWeapon()
{
}