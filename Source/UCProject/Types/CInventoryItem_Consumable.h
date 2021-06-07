#pragma once

#include "CoreMinimal.h"
#include "Types/CInventoryItem.h"
#include "TableDatas/ConsumableDesc.h"
#include "CInventoryItem_Consumable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStockChanged, UCInventoryItem_Consumable*, InConsumable, int32, InStock);

UCLASS(BlueprintType)
class UCPROJECT_API UCInventoryItem_Consumable : public UCInventoryItem
{
	GENERATED_BODY()

public:
	UCInventoryItem_Consumable();
	UCInventoryItem_Consumable* SetData(const FInventoryItemInput& InInput, const FConsumableDesc* InConsumableDesc, int32 InStock = 1);

	UCInventoryItem_Consumable* TakeOut(int32 InStock);
	void AddStock(int32 InStock);
	void Consum();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetStock() const { return Stock; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEmpty() const { return ConsumableDesc == nullptr; }

	FORCEINLINE const FConsumableDesc* GetConsumableDesc() const { return ConsumableDesc; };

public:
	UPROPERTY(BlueprintAssignable)
		FStockChanged OnStockChanged;

private:
	int32 Stock = 0;
	const FConsumableDesc* ConsumableDesc = nullptr;

};
