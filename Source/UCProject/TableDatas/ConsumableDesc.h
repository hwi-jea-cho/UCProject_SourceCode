#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types/MontageDesc.h"
#include "ConsumableDesc.generated.h"


USTRUCT(BlueprintType)
struct FConsumableDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACConsumableActor> ConsumableClass;

	UPROPERTY(EditAnywhere)
		FMontageDesc ConsumMontage;

};
