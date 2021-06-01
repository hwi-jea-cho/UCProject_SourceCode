#include "CInventoryItem_Consumable.h"
#include "Global.h"

UCInventoryItem_Consumable::UCInventoryItem_Consumable()
{

}

UCInventoryItem_Consumable* UCInventoryItem_Consumable::SetData(const FInventoryItemInput& InInput, const FConsumableDesc* InConsumableDesc, int32 InStock)
{
	Super::SetData(InInput);
	ConsumableDesc = InConsumableDesc;
	Stock = InStock;

	return this;
}

UCInventoryItem_Consumable* UCInventoryItem_Consumable::TakeOut(int32 InStock)
{
	int32 stock = UKismetMathLibrary::Clamp(0, Stock, InStock);
	Stock -= stock;

	if (OnStockChanged.IsBound())
		OnStockChanged.Broadcast(this, Stock);

	return NewObject<UCInventoryItem_Consumable>()->SetData(Input, ConsumableDesc, stock);
}

void UCInventoryItem_Consumable::AddStock(int32 InStock)
{
	Stock += InStock;

	if (OnStockChanged.IsBound())
		OnStockChanged.Broadcast(this, Stock);
}

void UCInventoryItem_Consumable::Consum()
{
	CheckTrue(Stock <= 0);

	--Stock;

	if (OnStockChanged.IsBound())
		OnStockChanged.Broadcast(this, Stock);
}
