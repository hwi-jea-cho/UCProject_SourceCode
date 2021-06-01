#include "CUserWidget_Consumable.h"
#include "Global.h"
#include "Components/PlayerOnly/CInventoryComponent.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"
#include "Types/CInventoryItem_Consumable.h"

void UCUserWidget_Consumable::Open()
{
	Player = GetOwningPlayerPawn();
	Inventory = CHelpers::GetComponent<UCInventoryComponent>(Player);
	QuickConsumable = CHelpers::GetComponent<UCQuickConsumableComponent>(Player);
	UpdateItemList();
	UpdateQuickItems();

	SetVisibility(ESlateVisibility::Visible);
}

void UCUserWidget_Consumable::Closs()
{
	SetVisibility(ESlateVisibility::Hidden);
}

int32 UCUserWidget_Consumable::GetConsumableCount() const
{
	CheckFalseResult(!!Inventory, 0);

	return Inventory->GetConsumableItemCount();
}

UCInventoryItem_Consumable* UCUserWidget_Consumable::GetConsumable(int32 InIndex)
{
	CheckFalseResult(!!Inventory, nullptr);
	CheckFalseResult(InIndex < Inventory->GetConsumableItemCount(), nullptr);

	return Inventory->GetConsumableItem(InIndex);
}

UCInventoryItem_Consumable* UCUserWidget_Consumable::GetItemQuick1()
{
	return QuickConsumable->GetItemQuick1();
}

UCInventoryItem_Consumable* UCUserWidget_Consumable::GetItemQuick2()
{
	return QuickConsumable->GetItemQuick2();
}

UCInventoryItem_Consumable* UCUserWidget_Consumable::GetItemQuick3()
{
	return QuickConsumable->GetItemQuick3();
}

UCInventoryItem_Consumable* UCUserWidget_Consumable::GetItemQuick4()
{
	return QuickConsumable->GetItemQuick4();
}

void UCUserWidget_Consumable::SetItemQuick1(UCInventoryItem_Consumable* InConsumable)
{
	QuickConsumable->SetItemQuick1(InConsumable);
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetItemQuick2(UCInventoryItem_Consumable* InConsumable)
{
	QuickConsumable->SetItemQuick2(InConsumable);
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetItemQuick3(UCInventoryItem_Consumable* InConsumable)
{
	QuickConsumable->SetItemQuick3(InConsumable);
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetItemQuick4(UCInventoryItem_Consumable* InConsumable)
{
	QuickConsumable->SetItemQuick4(InConsumable);
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetNullItemQuick1()
{
	QuickConsumable->SetNullItemQuick1();
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetNullItemQuick2()
{
	QuickConsumable->SetNullItemQuick2();
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetNullItemQuick3()
{
	QuickConsumable->SetNullItemQuick3();
	UpdateQuickItems();
}

void UCUserWidget_Consumable::SetNullItemQuick4()
{
	QuickConsumable->SetNullItemQuick4();
	UpdateQuickItems();
}
