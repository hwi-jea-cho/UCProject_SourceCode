#include "CInventoryItem.h"

UCInventoryItem::UCInventoryItem()
{

}

UCInventoryItem* UCInventoryItem::SetData(const FInventoryItemInput& InInput)
{
	Input = InInput;

	ItemID = InInput.ItemID;
	DisplayName = InInput.DisplayName;

	if (InInput.Desc != nullptr)
	{
		ItemType = InInput.Desc->ItemType;
		DetailDescription = InInput.Desc->DetailDescription;
	}
	else
	{
		ItemType = EItemType::None;
		DetailDescription = FText();
	}

	return this;
}
