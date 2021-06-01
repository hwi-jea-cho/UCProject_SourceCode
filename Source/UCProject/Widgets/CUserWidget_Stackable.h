#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Stackable.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_Stackable : public UUserWidget
{
	GENERATED_BODY()

public:
	void Open();
	void Closs();

	UFUNCTION(BlueprintPure)
		int32 GetEquipmentCount() const;

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetStackable(int32 InIndex);

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateItemList();

private:
	AActor* Player;
	class UCInventoryComponent* Inventory;
	class UCEquipmentComponent* Equipment;

};
