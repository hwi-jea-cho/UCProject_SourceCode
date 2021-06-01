#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Consumable.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_Consumable : public UUserWidget
{
	GENERATED_BODY()

public:
	void Open();
	void Closs();

	UFUNCTION(BlueprintPure)
		int32 GetConsumableCount() const;

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetConsumable(int32 InIndex);

	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick1();
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick2();
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick3();
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick4();

	UFUNCTION(BlueprintCallable)
		void SetItemQuick1(class UCInventoryItem_Consumable* InConsumable);
	UFUNCTION(BlueprintCallable)
		void SetItemQuick2(class UCInventoryItem_Consumable* InConsumable);
	UFUNCTION(BlueprintCallable)
		void SetItemQuick3(class UCInventoryItem_Consumable* InConsumable);
	UFUNCTION(BlueprintCallable)
		void SetItemQuick4(class UCInventoryItem_Consumable* InConsumable);

	UFUNCTION(BlueprintCallable)
		void SetNullItemQuick1();
	UFUNCTION(BlueprintCallable)
		void SetNullItemQuick2();
	UFUNCTION(BlueprintCallable)
		void SetNullItemQuick3();
	UFUNCTION(BlueprintCallable)
		void SetNullItemQuick4();

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateItemList();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateQuickItems();

private:
	AActor* Player;
	class UCInventoryComponent* Inventory;
	class UCQuickConsumableComponent* QuickConsumable;

};
