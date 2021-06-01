#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/Character/CNpcPoseComponent.h"
#include "CAnimInstance_NPC.generated.h"

UCLASS()
class UCPROJECT_API UCAnimInstance_NPC : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Hoz;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Vert;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		ENpcPoseType CurrPose;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float RotationSpeed = 1080.0f;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	float AdjustmentAngle(float InMaxDelta, float InOldAngle, float InNewAngle);

private:
	UCNpcPoseComponent* Pose;

	float PrevHoz;
	float PrevVert;
};
