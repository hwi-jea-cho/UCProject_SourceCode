#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_QuickSlots.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_QuickSlots : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick1();
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick2();
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick3();
	UFUNCTION(BlueprintPure)
		class UCInventoryItem_Consumable* GetItemQuick4();

public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateQuickSlots();

	void BeginPlay();

private:
	class UCQuickConsumableComponent* QuickConsumable;

};
