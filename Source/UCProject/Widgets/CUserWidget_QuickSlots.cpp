#include "CUserWidget_QuickSlots.h"
#include "Global.h"
#include "Components/TextBlock.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"
#include "Types/CInventoryItem_Consumable.h"

UCInventoryItem_Consumable* UCUserWidget_QuickSlots::GetItemQuick1()
{
	return QuickConsumable->GetItemQuick1();
}

UCInventoryItem_Consumable* UCUserWidget_QuickSlots::GetItemQuick2()
{
	return QuickConsumable->GetItemQuick2();
}

UCInventoryItem_Consumable* UCUserWidget_QuickSlots::GetItemQuick3()
{
	return QuickConsumable->GetItemQuick3();
}

UCInventoryItem_Consumable* UCUserWidget_QuickSlots::GetItemQuick4()
{
	return QuickConsumable->GetItemQuick4();
}

void UCUserWidget_QuickSlots::BeginPlay()
{
	AActor* Player = GetOwningPlayerPawn();
	QuickConsumable = CHelpers::GetComponent<UCQuickConsumableComponent>(Player);

	UpdateQuickSlots();
}
