#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TableDatas/ItemDatas.h"
#include "CEquipmentItem.generated.h"

UCLASS()
class UCPROJECT_API UCEquipmentItem : public UObject
{
	GENERATED_BODY()

public:
	UCEquipmentItem();
	UCEquipmentItem* SetData(FName InItemID, const FEquipmentItemDesc* InDesc);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE FName GetItemID() const { return ItemID; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE EEquipmentType GetEquipmentType() const { return (!!Desc) ? Desc->EquipmentType : EEquipmentType::None; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE FStatusData GetStatus() const { return Desc->Status; }

private:
	FName ItemID = "None";
	const FEquipmentItemDesc* Desc = nullptr;
};
