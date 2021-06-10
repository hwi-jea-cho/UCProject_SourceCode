#include "CEquipmentComponent.h"
#include "Global.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Types/CEquipmentItem.h"
#include "DataAssets/CWeaponData.h"
#include "TableDatas/WeaponDesc.h"
#include "CStateComponent.h"
#include "CStatusComponent.h"
#include "Actors/CAttachment.h"

UCEquipmentComponent::UCEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CHelpers::GetAsset(&DefaultWeaponData,
		"CWeaponData'/Game/_MyWorld/DataAssets/Equipment/Player/Sword/DA_Sword.DA_Sword'");

	CHelpers::GetAsset(&WeaponList,
		"DataTable'/Game/_MyWorld/DataTables/Player/FPlayerWeaponList.FPlayerWeaponList'");

}

void UCEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	DefaultWeapon = DefaultWeaponData->Spawn(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	StatusWeapon = NewObject<UCStatusInstance>();
	StatusArmor = NewObject<UCStatusInstance>();
	StatusAccessory = NewObject<UCStatusInstance>();

	UCStatusComponent* Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	if (!!Status)
	{
		Status->AddChild(StatusWeapon);
		Status->AddChild(StatusArmor);
		Status->AddChild(StatusAccessory);
	}
}

void UCEquipmentComponent::EquipWeapon(UCEquipmentItem* InItem)
{
	CheckTrue(Weapon == InItem);

	NextWeapon = InItem;

	if (!!NextWeapon)
		if (NextWeapon->GetEquipmentType() != EEquipmentType::Weapon)
			NextWeapon = nullptr;
	bTriggerNextWeapon = true;

	if (!!State)
	{
		if (State->IsIdleMode())
			ChangeWeapon();

	}
	else
	{
		ChangeWeapon();
	}

}

void UCEquipmentComponent::EquipArmor(UCEquipmentItem* InItem)
{
	CheckTrue(Armor == InItem);

	Armor = InItem;

	if (!!Armor)
	{
		if (Armor->GetEquipmentType() != EEquipmentType::Armor)
			Armor = nullptr;

		StatusArmor->SetLocalData(Armor->GetStatus());
	}
	else
	{
		StatusArmor->SetLocalData(FStatusData());
	}

}

void UCEquipmentComponent::EquipAccessory(UCEquipmentItem* InItem)
{
	CheckTrue(Accessory == InItem);

	Accessory = InItem;

	if (!!Accessory)
	{
		if (Accessory->GetEquipmentType() != EEquipmentType::Accessory)
			Accessory = nullptr;

		StatusAccessory->SetLocalData(Accessory->GetStatus());
	}
	else
	{
		StatusAccessory->SetLocalData(FStatusData());
	}

}


void UCEquipmentComponent::ChangeWeapon()
{
	CheckFalse(bTriggerNextWeapon);
	bTriggerNextWeapon = false;

	if (!!EquipedWeapon)
		EquipedWeapon->Destroy();

	FString contextString;
	FWeaponDesc* weaponDesc = nullptr;
	if (!!NextWeapon)
		weaponDesc = WeaponList->FindRow<FWeaponDesc>(NextWeapon->GetItemID(), contextString);

	Weapon = NextWeapon;
	NextWeapon = nullptr;

	if (!!Weapon)
		StatusWeapon->SetLocalData(Weapon->GetStatus());
	else
		StatusWeapon->SetLocalData(FStatusData());

	if (!!weaponDesc)
	{
		EquipedWeapon = weaponDesc->WeaponData->Spawn(OwnerCharacter);
		DefaultWeapon->SetActorHiddenInGame(true);
	}
	else
	{
		EquipedWeapon = nullptr;

		DefaultWeapon->SetActorHiddenInGame(false);
		DefaultWeapon->End_Unequip();
	}

}
FName UCEquipmentComponent::GetEquipedWeapon() const
{ 
	return Weapon->GetItemID(); 
}
