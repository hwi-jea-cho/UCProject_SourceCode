#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangedEquipment, class ACAttachment*, InNewEquipment);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		class UCWeaponData* DefaultWeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		class UDataTable* WeaponList;

public:
	UCEquipmentComponent();

protected:
	virtual void BeginPlay() override;

public:
	void EquipWeapon(class UCEquipmentItem* InItem);
	void EquipArmor(class UCEquipmentItem* InItem);
	void EquipAccessory(class UCEquipmentItem* InItem);
	void ChangeWeapon();

public:
	FChangedEquipment OnChangedWeapon;

private:
	UPROPERTY() class UCEquipmentItem* Weapon;
	UPROPERTY() class UCEquipmentItem* Armor;
	UPROPERTY() class UCEquipmentItem* Accessory;
	UPROPERTY() class UCStatusInstance* StatusWeapon;
	UPROPERTY() class UCStatusInstance* StatusArmor;
	UPROPERTY() class UCStatusInstance* StatusAccessory;

private:
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class ACAttachment* DefaultWeapon;
	class ACAttachment* EquipedWeapon;
	UPROPERTY() class UCEquipmentItem* NextWeapon;
	bool bTriggerNextWeapon = false;

public:
	FORCEINLINE class ACAttachment* GetEquipedWeapon() const {
		return (!!EquipedWeapon) ? EquipedWeapon : DefaultWeapon;
	}

};
