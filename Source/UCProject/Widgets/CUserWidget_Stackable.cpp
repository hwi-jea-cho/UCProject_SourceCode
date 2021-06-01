#include "CUserWidget_Stackable.h"
#include "Global.h"
#include "Components/PlayerOnly/CInventoryComponent.h"
#include "Types/CInventoryItem_Consumable.h"

void UCUserWidget_Stackable::Open()
{
	Player = GetOwningPlayerPawn();
	Inventory = CHelpers::GetComponent<UCInventoryComponent>(Player);
	UpdateItemList();

	SetVisibility(ESlateVisibility::Visible);
}

void UCUserWidget_Stackable::Closs()
{
	SetVisibility(ESlateVisibility::Hidden);
}

int32 UCUserWidget_Stackable::GetEquipmentCount() const
{
	CheckFalseResult(!!Inventory, 0);

	return Inventory->GetConsumableItemCount();
}

UCInventoryItem_Consumable* UCUserWidget_Stackable::GetStackable(int32 InIndex)
{
	CheckFalseResult(!!Inventory, nullptr);
	CheckFalseResult(InIndex < Inventory->GetConsumableItemCount(), nullptr);

	return Inventory->GetConsumableItem(InIndex);
}
