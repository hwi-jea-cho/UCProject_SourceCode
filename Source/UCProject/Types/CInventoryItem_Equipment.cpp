#include "CInventoryItem_Equipment.h"
#include "Types/CEquipmentItem.h"

UCInventoryItem_Equipment::UCInventoryItem_Equipment()
{

}

UCInventoryItem_Equipment* UCInventoryItem_Equipment::SetData(const FInventoryItemInput& InInput, const FEquipmentItemDesc* InEquipmentDesc)
{
    Super::SetData(InInput);
    EquipmentItem = NewObject<UCEquipmentItem>()->SetData(InInput.ItemID, InEquipmentDesc);

    return this;
}
