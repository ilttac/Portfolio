#include "CAnimInstance.h"
#include "Global.h"
#include "CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAnimInstance::UCAnimInstance()
{
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACPlayer* player = ACPlayer::GetInstance();
	//UActorComponent* actorComponent = player->GetComponentByClass(UCIk::StaticClass());
	////Foot = Cast<UCIk>(actorComponent);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* charactor = Cast<ACharacter>(TryGetPawnOwner());
	RetNull(charactor);

	Speed = charactor->GetVelocity().Size();
	Direction = CalculateDirection(charactor->GetVelocity(), charactor->GetActorRotation());
	bInAir = charactor->GetCharacterMovement()->IsFalling();

	ACPlayer* player = Cast<ACPlayer>(charactor);
	RetNull(player);

	bDrawing = player->GetDrawing();
	bSheathing = player->GetSheathing();
	SetRollPitchYaw();
	SetYawDeltaforLens(DeltaSeconds);
	SetAccelerating();
	SetFullBody();
	/*RetNull(Foot);
	FootIk = Foot->GetIk();*/
}
void UCAnimInstance::SetRollPitchYaw()
{
	ACharacter* charactor = Cast<ACharacter>(TryGetPawnOwner());
	RetNull(charactor);

	ACPlayer* player = Cast<ACPlayer>(charactor);
	RetNull(player);

	FRotator animRotation = player->GetBaseAimRotation();
	FRotator actorRotation = player->GetActorRotation();

	FRotator rotation = UKismetMathLibrary::NormalizedDeltaRotator(animRotation, actorRotation);

	Pitch = rotation.Pitch;
	Roll = rotation.Roll;
	Yaw = rotation.Yaw;

}

void UCAnimInstance::SetYawDeltaforLens(float DeltaSeconds)
{
	ACharacter* charactor = Cast<ACharacter>(TryGetPawnOwner());
	RetNull(charactor);

	ACPlayer* player = Cast<ACPlayer>(charactor);
	RetNull(player);

	FRotator actorRotation = player->GetActorRotation();
	RotationLastTick = actorRotation;
	FRotator rotation = UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, actorRotation);

	YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, (RotationLastTick.Yaw / DeltaSeconds) / 7.0f, DeltaSeconds, 6.0f);
}
void UCAnimInstance::SetAccelerating()
{
	ACharacter* charactor = Cast<ACharacter>(TryGetPawnOwner());
	RetNull(charactor);
	FVector accelVector = charactor->GetCharacterMovement()->GetCurrentAcceleration();
	if (UKismetMathLibrary::VSize(accelVector) > 0)
	{
		bIsAccelerating = true;
	}
	else
	{
		bIsAccelerating = false;
	}
}
void UCAnimInstance::SetFullBody()
{
	if (GetCurveValue("FullBody") > 0.0f)
	{
		bFullBody = true;
	}
	else
	{
		bFullBody = false;
	}

	PistolHolster  = GetCurveValue("Ult_Pistol_ON")*-1.0f +1.0f;
}