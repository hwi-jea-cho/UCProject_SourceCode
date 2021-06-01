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
		EStanceType StanceType;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void StanceChanged(EStanceType InPrevType, EStanceType InNewType);

};
