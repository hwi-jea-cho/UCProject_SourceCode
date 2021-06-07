#include "CQuickConsumableComponent.h"
#include "Global.h"
#include "Types/CInventoryItem_Consumable.h"
#include "Types/CQuickConsumable_Staff.h"
#include "Actors/CConsumableActor.h"

UCQuickConsumableComponent::UCQuickConsumableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCQuickConsumableComponent::BeginPlay()
{
	Super::BeginPlay();

	QuickSlot1 = NewObject<UCQuickConsumable_Staff>();
	QuickSlot2 = NewObject<UCQuickConsumable_Staff>();
	QuickSlot3 = NewObject<UCQuickConsumable_Staff>();
	QuickSlot4 = NewObject<UCQuickConsumable_Staff>();

	QuickSlot1->SetOwner(GetOwner());
	QuickSlot2->SetOwner(GetOwner());
	QuickSlot3->SetOwner(GetOwner());
	QuickSlot4->SetOwner(GetOwner());
}


void UCQuickConsumableComponent::OnQuick1()
{
	StartComsum(QuickSlot1->GetItemActor());
}

void UCQuickConsumableComponent::OnQuick2()
{
	StartComsum(QuickSlot2->GetItemActor());
}

void UCQuickConsumableComponent::OnQuick3()
{
	StartComsum(QuickSlot3->GetItemActor());
}

void UCQuickConsumableComponent::OnQuick4()
{
	StartComsum(QuickSlot4->GetItemActor());
}

void UCQuickConsumableComponent::SetNullItemQuick1()
{
	SetNullItemQuick(QuickSlot1);
}

void UCQuickConsumableComponent::SetNullItemQuick2()
{
	SetNullItemQuick(QuickSlot2);
}

void UCQuickConsumableComponent::SetNullItemQuick3()
{
	SetNullItemQuick(QuickSlot3);
}

void UCQuickConsumableComponent::SetNullItemQuick4()
{
	SetNullItemQuick(QuickSlot4);
}

void UCQuickConsumableComponent::SetItemQuick1(UCInventoryItem_Consumable* InConsumable)
{
	SetItemQuick(QuickSlot1, InConsumable);
}

void UCQuickConsumableComponent::SetItemQuick2(UCInventoryItem_Consumable* InConsumable)
{
	SetItemQuick(QuickSlot2, InConsumable);
}

void UCQuickConsumableComponent::SetItemQuick3(UCInventoryItem_Consumable* InConsumable)
{
	SetItemQuick(QuickSlot3, InConsumable);
}

void UCQuickConsumableComponent::SetItemQuick4(UCInventoryItem_Consumable* InConsumable)
{
	SetItemQuick(QuickSlot4, InConsumable);
}

UCInventoryItem_Consumable* UCQuickConsumableComponent::GetItemQuick1()
{
	return QuickSlot1->GetItem();
}

UCInventoryItem_Consumable* UCQuickConsumableComponent::GetItemQuick2()
{
	return QuickSlot2->GetItem();
}

UCInventoryItem_Consumable* UCQuickConsumableComponent::GetItemQuick3()
{
	return QuickSlot3->GetItem();
}

UCInventoryItem_Consumable* UCQuickConsumableComponent::GetItemQuick4()
{
	return QuickSlot4->GetItem();
}


void UCQuickConsumableComponent::SetNullItemQuick(UCQuickConsumable_Staff* InQuick)
{
	InQuick->SetNullConsumable();
}

void UCQuickConsumableComponent::SetItemQuick(UCQuickConsumable_Staff* InQuick, UCInventoryItem_Consumable* InConsumable)
{
	CheckNull(InConsumable);
	InQuick->SetConsumable(InConsumable);

}

void UCQuickConsumableComponent::StartComsum(ACConsumableActor* InConsumable)
{
	CheckTrue(CurrQuickActor != nullptr);
	CheckNull(InConsumable);

	CurrQuickActor = InConsumable;
	InConsumable->End_Consum.AddDynamic(this, &UCQuickConsumableComponent::End_Comsum);
	InConsumable->StartConsum();
}

// ACConsumableActor::End_Consum
void UCQuickConsumableComponent::End_Comsum()
{
	CurrQuickActor->End_Consum.RemoveDynamic(this, &UCQuickConsumableComponent::End_Comsum);
	CurrQuickActor = nullptr;
}
