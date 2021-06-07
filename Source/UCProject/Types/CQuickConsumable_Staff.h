#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CQuickConsumable_Staff.generated.h"

/***
  �� ���� 1���� ����
***/
UCLASS()
class UCPROJECT_API UCQuickConsumable_Staff : public UObject
{
	GENERATED_BODY()
	
public:
	void SetOwner(AActor* InOwnerActor);
	void SetConsumable(class UCInventoryItem_Consumable* InItem);
	void SetNullConsumable();

private:
	void UpdateConsumActor();

	UFUNCTION()
		void Begin_Consum();

	UFUNCTION()
		void End_Consum();

	UFUNCTION()
		void OnStockChanged(class UCInventoryItem_Consumable* InConsumable, int32 InStock);

public:
	// ���̱��, �Һ� ���̸� �Һ� �� �Ŀ� Consumable ��ü
	FORCEINLINE class UCInventoryItem_Consumable* GetItem() { return InputItem; }
	FORCEINLINE class ACConsumableActor* GetItemActor() { return Consumable; }

private:
	bool bConsuming = false;
	class UCInventoryItem_Consumable* InputItem;
	class ACConsumableActor* Consumable;

private:
	AActor* OwnerActor;
	class UCMenuComponent* Menu;

};
