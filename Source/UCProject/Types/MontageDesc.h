#pragma once

#include "CoreMinimal.h"
#include "MontageDesc.generated.h"

USTRUCT(BlueprintType)
struct FMontageDesc
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSction;

};
