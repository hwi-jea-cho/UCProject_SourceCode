#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponDesc.generated.h"


USTRUCT(BlueprintType)
struct FWeaponDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UCWeaponData* WeaponData;
};

