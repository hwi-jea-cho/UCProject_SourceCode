#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types/CStatusInstance.h"
#include "ItemDatas.generated.h"

// -- Enums -- //

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, Equipment, Consumable
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	None, Weapon, Armor, Accessory
};


// -- FTableRowBases -- //

USTRUCT(BlueprintType)
struct FInventoryItemDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EItemType ItemType;

	UPROPERTY(EditAnywhere)
		FText DetailDescription;

};

USTRUCT(BlueprintType)
struct FEquipmentItemDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FStatusData Status;

};



