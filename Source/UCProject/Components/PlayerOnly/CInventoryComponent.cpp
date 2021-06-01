#include "CInventoryComponent.h"
#include "Global.h"
#include "Types/CInventoryItem_Equipment.h"
#include "Types/CInventoryItem_Consumable.h"
#include "Types/CEquipmentItem.h"
#include "TableDatas/InteractorDesc.h"
#include "TableDatas/ConsumableDesc.h"
#include "Components/Actor/CInteractorComponent.h"


UCInventoryComponent::UCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


	CHelpers::GetAsset(&InventoryItemTable,
		"DataTable'/Game/_MyWorld/DataTables/FInventoryItemList.FInventoryItemList'");

	CHelpers::GetAsset(&EquipmentItemTable,
		"DataTable'/Game/_MyWorld/DataTables/FEquipmentItemList.FEquipmentItemList'");

	CHelpers::GetAsset(&ConsumableTable,
		"DataTable'/Game/_MyWorld/DataTables/FConsumableList.FConsumableList'");

}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Interactor = CHelpers::GetComponent<UCInteractorComponent>(GetOwner());

	StatusCharacter = NewObject<UCStatusInstance>();
	StatusEquipment = NewObject<UCStatusInstance>();
	StatusWeapon = NewObject<UCStatusInstance>();
	StatusArmor = NewObject<UCStatusInstance>();
	StatusAccessory = NewObject<UCStatusInstance>();

	StatusEquipment->SetParent(StatusCharacter);
	StatusWeapon->SetParent(StatusEquipment);
	StatusArmor->SetParent(StatusEquipment);
	StatusAccessory->SetParent(StatusEquipment);
}


// -- public -- //

void UCInventoryComponent::AddItem(FName InItemID, int32 InItemCount)
{
	FInventoryItemInput input;
	input.ItemID = InItemID;

	FString ContextString;
	if (!!InventoryItemTable)
		input.Desc = InventoryItemTable->FindRow<FInventoryItemDesc>(InItemID, ContextString);

	CheckNull(input.Desc);

	if (!!Interactor)
	{
		input.DisplayName = Interactor->ConvertIdToName(InItemID);

		if (input.DisplayName.IsEmpty())
			input.DisplayName = Interactor->ConvertIdToName("Default");
	}

	switch (input.Desc->ItemType)
	{
	case EItemType::Consumable: AddItemConsumable(input, InItemCount); break;
	case EItemType::Equipment: AddItemEquipment(input); break;
	default: break;
	}
}

void UCInventoryComponent::Equip(UCInventoryItem_Equipment* InEquipment)
{
	CheckFalse(!!InEquipment);

	switch (InEquipment->GetEquipment()->GetEquipmentType())
	{
	case EEquipmentType::Weapon: EquipWeapon(InEquipment); break;
	case EEquipmentType::Armor: EquipArmor(InEquipment); break;
	case EEquipmentType::Accessory: EquipAccessory(InEquipment); break;
	default: break;
	}
}

void UCInventoryComponent::UnequipWeapon()
{
	CheckFalse(!!Weapon);

	EquipmentItems.Add(Weapon);
	Weapon = nullptr;

	StatusWeapon->SetLocalData(FStatusData());
}

void UCInventoryComponent::UnequipArmor()
{
	CheckFalse(!!Armor);

	EquipmentItems.Add(Armor);
	Armor = nullptr;

	StatusArmor->SetLocalData(FStatusData());
}

void UCInventoryComponent::UnequipAccessory()
{
	CheckFalse(!!Accessory);

	EquipmentItems.Add(Accessory);
	Accessory = nullptr;
	StatusAccessory->SetLocalData(FStatusData());
}

void UCInventoryComponent::SetCharacterStatus(FStatusData InStatus)
{
	StatusCharacter->SetLocalData(InStatus);

}

FStatusData UCInventoryComponent::GetCharacterStatus() const
{
	return StatusCharacter->GetData();
}

FStatusData UCInventoryComponent::GetEquipmentStatus() const
{
	return StatusEquipment->GetData();
}


// -- private -- //

void UCInventoryComponent::AddItemConsumable(const FInventoryItemInput& InInput, int32 InItemCount)
{
	UCInventoryItem_Consumable* consumable = nullptr;
	for (UCInventoryItem_Consumable* item : ConsumableItems)
	{
		if (item->GetItemID() == InInput.ItemID)
		{
			consumable = item;
			break;
		}
	}

	if (!!consumable)
	{
		consumable->AddStock(InItemCount);
	}
	else
	{
		const FConsumableDesc* consumableDesc = nullptr;

		FString ContextString;
		if (!!ConsumableTable)
			consumableDesc = ConsumableTable->FindRow<FConsumableDesc>(InInput.ItemID, ContextString);

		consumable = NewObject<UCInventoryItem_Consumable>()->
			SetData(InInput, consumableDesc, InItemCount);
		consumable->OnStockChanged.AddDynamic(this, &UCInventoryComponent::OnStockChanged);
		ConsumableItems.Add(consumable);
	}

}

void UCInventoryComponent::AddItemEquipment(const FInventoryItemInput& InInput)
{
	const FEquipmentItemDesc* equipmentitemDesc = nullptr;

	FString ContextString;
	if (!!EquipmentItemTable)
		equipmentitemDesc = EquipmentItemTable->FindRow<FEquipmentItemDesc>(InInput.ItemID, ContextString);

	CheckNull(equipmentitemDesc);

	EquipmentItems.Add(NewObject<UCInventoryItem_Equipment>()->
		SetData(InInput, equipmentitemDesc));
}


void UCInventoryComponent::EquipWeapon(UCInventoryItem_Equipment* InEquipment)
{
	UnequipWeapon();
	EquipmentItems.Remove(InEquipment);
	Weapon = InEquipment;

	if (!!Weapon)
		StatusWeapon->SetLocalData(Weapon->GetEquipment()->GetStatus());
}

void UCInventoryComponent::EquipArmor(UCInventoryItem_Equipment* InEquipment)
{
	UnequipArmor();
	EquipmentItems.Remove(InEquipment);
	Armor = InEquipment;

	if (!!Armor)
		StatusArmor->SetLocalData(Armor->GetEquipment()->GetStatus());
}

void UCInventoryComponent::EquipAccessory(UCInventoryItem_Equipment* InEquipment)
{
	UnequipAccessory();
	EquipmentItems.Remove(InEquipment);
	Accessory = InEquipment;

	if (!!Accessory)
		StatusAccessory->SetLocalData(Accessory->GetEquipment()->GetStatus());
}

void UCInventoryComponent::OnStockChanged(UCInventoryItem_Consumable* InConsumable, int32 Stock)
{
	CheckTrue(Stock != 0);

	ConsumableItems.Remove(InConsumable);

}
