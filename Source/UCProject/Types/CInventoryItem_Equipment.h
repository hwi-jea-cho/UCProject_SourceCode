#pragma once

#include "CoreMinimal.h"
#include "Types/CInventoryItem.h"
#include "CInventoryItem_Equipment.generated.h"

UCLASS()
class UCPROJECT_API UCInventoryItem_Equipment : public UCInventoryItem
{
	GENERATED_BODY()

public:
	UCInventoryItem_Equipment();
	UCInventoryItem_Equipment* SetData(const FInventoryItemInput& InInput, const FEquipmentItemDesc* InEquipmentDesc);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCEquipmentItem* GetEquipment() const { return EquipmentItem; }

private:
	UPROPERTY() class UCEquipmentItem* EquipmentItem;

};
