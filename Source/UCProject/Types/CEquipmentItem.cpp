#include "CEquipmentItem.h"

UCEquipmentItem::UCEquipmentItem()
{

}

UCEquipmentItem* UCEquipmentItem::SetData(FName InItemID, const FEquipmentItemDesc* InDesc)
{
	ItemID = InItemID;
	Desc = InDesc;
	return this;
}
