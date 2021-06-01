#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/CStatusInstance.h"
#include "CUserWidget_Equipment.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_Equipment : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void Equip(int32 InIndex);

	UFUNCTION(BlueprintCallable)
		void UnequipWeapon();

	UFUNCTION(BlueprintCallable)
		void UnequipArmor();

	UFUNCTION(BlueprintCallable)
		void UnequipAccessory();

	void Open();
	void Closs();

	UFUNCTION(BlueprintPure)
		int32 GetEquipmentCount() const;

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Equipment* GetEquipment(int32 InIndex);

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Equipment* GetEquipedWeapon() const;

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Equipment* GetEquipedArmor() const;

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Equipment* GetEquipedAccessory() const;

	UFUNCTION(BlueprintPure)
		FStatusData GetEquipmentStatus() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateEquipmentList();

private:
	AActor* Player;
	class UCInventoryComponent* Inventory;
	class UCEquipmentComponent* Equipment;

};
