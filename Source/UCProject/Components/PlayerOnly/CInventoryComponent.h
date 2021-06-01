#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CInventoryItem.h"
#include "Types/CStatusInstance.h"
#include "TableDatas/ItemDatas.h"
#include "CInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		UDataTable* InventoryItemTable;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		UDataTable* EquipmentItemTable;

	UPROPERTY(EditDefaultsOnly, Category = "Consumable")
		UDataTable* ConsumableTable;

public:	
	UCInventoryComponent();

protected:
	virtual void BeginPlay() override;


public:	
	UFUNCTION(BlueprintCallable)
		void AddItem(FName InItemID, int32 InItemCount);

	UFUNCTION(BlueprintCallable)
		void Equip(class UCInventoryItem_Equipment* InEquipment);
	
	UFUNCTION(BlueprintCallable)
		void UnequipWeapon();

	UFUNCTION(BlueprintCallable)
		void UnequipArmor();

	UFUNCTION(BlueprintCallable)
		void UnequipAccessory();

	void SetCharacterStatus(FStatusData InStatus);
	FStatusData GetCharacterStatus() const;
	FStatusData GetEquipmentStatus() const;

private:
	void AddItemConsumable(const FInventoryItemInput& InInput, int32 InItemCount);
	void AddItemEquipment(const FInventoryItemInput& InInput);
	void EquipWeapon(class UCInventoryItem_Equipment* InEquipment);
	void EquipArmor(class UCInventoryItem_Equipment* InEquipment);
	void EquipAccessory(class UCInventoryItem_Equipment* InEquipment);
	
	UFUNCTION()
		void OnStockChanged(UCInventoryItem_Consumable* InConsumable, int32 Stock);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetConsumableItemCount() const { return ConsumableItems.Num(); }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCInventoryItem_Consumable* GetConsumableItem(int32 InIndex) { return ConsumableItems[InIndex]; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetEquipmentItemCount() const { return EquipmentItems.Num(); }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCInventoryItem_Equipment* GetEquipmentItem(int32 InIndex) { return EquipmentItems[InIndex]; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCInventoryItem_Equipment* GetWeapon() { return Weapon; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCInventoryItem_Equipment* GetArmor() { return Armor; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCInventoryItem_Equipment* GetAccessory() { return Accessory; }


private:
	class UCInteractorComponent* Interactor;
	UPROPERTY()
		TArray<class UCInventoryItem_Consumable*> ConsumableItems;
	UPROPERTY()
		TArray<class UCInventoryItem_Equipment*> EquipmentItems;
	UPROPERTY() class UCInventoryItem_Equipment* Weapon;
	UPROPERTY() class UCInventoryItem_Equipment* Armor;
	UPROPERTY() class UCInventoryItem_Equipment* Accessory;

private:
	UPROPERTY() UCStatusInstance* StatusCharacter;
	UPROPERTY() UCStatusInstance* StatusEquipment;
	UPROPERTY() UCStatusInstance* StatusWeapon;
	UPROPERTY() UCStatusInstance* StatusArmor;
	UPROPERTY() UCStatusInstance* StatusAccessory;

};
