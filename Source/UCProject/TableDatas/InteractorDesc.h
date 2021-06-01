#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InteractorDesc.generated.h"

USTRUCT(BlueprintType)
struct UCPROJECT_API FInteractorDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FText DisplayName;

};
