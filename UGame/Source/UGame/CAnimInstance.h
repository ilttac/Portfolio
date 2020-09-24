#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
//#include "CIk.h"
#include "CAnimInstance.generated.h"

UCLASS()
class UGAME_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMax = 600, ClampMin = 0))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMax = 180, ClampMin = -180))
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bDrawing;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bSheathing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Roll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float YawDelta;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	FIk FootIk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float PistolHolster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRotator RotationLastTick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bFullBody;

public:
	UFUNCTION()
		void SetRollPitchYaw();
	
	UFUNCTION()
		void SetYawDeltaforLens(float DeltaSeconds);

	UFUNCTION()
		void SetAccelerating();

	UFUNCTION()
		void SetFullBody();

public:
	UCAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	//class UCIk* Foot;
};
