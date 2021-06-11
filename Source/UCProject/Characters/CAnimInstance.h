#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/Character/CStanceComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class UCPROJECT_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsCrouching;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float HeadHoz;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float HeadVert;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float HeadSpeed = 720.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EStanceType StanceType;
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	float AdjustmentAngle(float InMaxDelta, float InOldAngle, float InNewAngle);

private:
	UFUNCTION()
		void OnChangedStance(EStanceType InPrevType, EStanceType InNewType);

	UFUNCTION()
		void OnChangedHeadRotation(FRotator InRotator);

private:
	float PrevHoz;
	float PrevVert;
	float TargetHoz;
	float TargetVert;
};
