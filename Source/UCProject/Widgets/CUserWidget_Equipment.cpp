#include "CUserWidget_Equipment.h"
#include "Global.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Components/PlayerOnly/CInventoryComponent.h"
#include "Types/CInventoryItem_Equipment.h"
#include "Types/CEquipmentItem.h"

void UCUserWidget_Equipment::Equip(int32 InIndex)
{
	CheckFalse(!!Inventory);
	CheckFalse(InIndex < Inventory->GetEquipmentItemCount());

	Inventory->Equip(Inventory->GetEquipmentItem(InIndex));
	UpdateEquipmentList();

	bIsFocusable = true;
}

void UCUserWidget_Equipment::UnequipWeapon()
{
	CheckFalse(!!Inventory);

	Inventory->UnequipWeapon();
	UpdateEquipmentList();
}

void UCUserWidget_Equipment::UnequipArmor()
{
	CheckFalse(!!Inventory);

	Inventory->UnequipArmor();
	UpdateEquipmentList();
}

void UCUserWidget_Equipment::UnequipAccessory()
{
	CheckFalse(!!Inventory);

	Inventory->UnequipAccessory();
	UpdateEquipmentList();
}


void UCUserWidget_Equipment::Open()
{
	Player = GetOwningPlayerPawn();
	Inventory = CHelpers::GetComponent<UCInventoryComponent>(Player);
	Equipment = CHelpers::GetComponent<UCEquipmentComponent>(Player);

	UpdateEquipmentList();
	SetVisibility(ESlateVisibility::Visible);
}

void UCUserWidget_Equipment::Closs()
{
	if ((!!Equipment) && (!!Inventory))
	{
		UCInventoryItem_Equipment* item;
		UCEquipmentItem* equipment;

		equipment = nullptr;
		item = Inventory->GetWeapon();
		if (!!item) equipment = item->GetEquipment();
		Equipment->EquipWeapon(equipment);

		equipment = nullptr;
		item = Inventory->GetArmor();
		if (!!item) equipment = item->GetEquipment();
		Equipment->EquipArmor(equipment);

		equipment = nullptr;
		item = Inventory->GetAccessory();
		if (!!item) equipment = item->GetEquipment();
		Equipment->EquipAccessory(equipment);
	}

	SetVisibility(ESlateVisibility::Hidden);
}


int32 UCUserWidget_Equipment::GetEquipmentCount() const
{
	CheckFalseResult(!!Inventory, 0);

	return Inventory->GetEquipmentItemCount();
}

UCInventoryItem_Equipment* UCUserWidget_Equipment::GetEquipment(int32 InIndex)
{
	CheckFalseResult(!!Inventory, nullptr);
	CheckFalseResult(InIndex >= 0, nullptr);
	CheckFalseResult(InIndex < Inventory->GetEquipmentItemCount(), nullptr);

	return Inventory->GetEquipmentItem(InIndex);
}

UCInventoryItem_Equipment* UCUserWidget_Equipment::GetEquipedWeapon() const
{
	CheckFalseResult(!!Inventory, nullptr);

	return Inventory->GetWeapon();
}

UCInventoryItem_Equipment* UCUserWidget_Equipment::GetEquipedArmor() const
{
	CheckFalseResult(!!Inventory, nullptr);

	return Inventory->GetArmor();
}

UCInventoryItem_Equipment* UCUserWidget_Equipment::GetEquipedAccessory() const
{
	CheckFalseResult(!!Inventory, nullptr);

	return Inventory->GetAccessory();
}

FStatusData UCUserWidget_Equipment::GetEquipmentStatus() const
{
	return Inventory->GetEquipmentStatus();
}
