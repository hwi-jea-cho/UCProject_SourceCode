#include "CQuickConsumable_Staff.h"
#include "Global.h"
#include "Types/CInventoryItem_Consumable.h"
#include "Components/PlayerOnly/CMenuComponent.h"
#include "Actors/CConsumableActor.h"
#include "TableDatas/ConsumableDesc.h"

void UCQuickConsumable_Staff::SetOwner(AActor* InOwnerActor)
{
	OwnerActor = InOwnerActor;
	Menu = CHelpers::GetComponent<UCMenuComponent>(InOwnerActor);
}

// 사용아이템 교체 (준비)
void UCQuickConsumable_Staff::SetConsumable(UCInventoryItem_Consumable* InItem)
{
	if (InItem == nullptr)
	{
		SetNullConsumable();
		return;
	}

	if (InItem->IsEmpty())
	{
		return;
	}

	InputItem = InItem;
	Menu->UpdateQuickSlots();
	InputItem->OnStockChanged.AddDynamic(this, &UCQuickConsumable_Staff::OnStockChanged);

	UpdateConsumActor();

}

void UCQuickConsumable_Staff::SetNullConsumable()
{
	if (!!InputItem)
		InputItem->OnStockChanged.RemoveDynamic(this, &UCQuickConsumable_Staff::OnStockChanged);

	InputItem = nullptr;
	Menu->UpdateQuickSlots();

	UpdateConsumActor();
}


void UCQuickConsumable_Staff::Begin_Consum()
{
	bConsuming = true;
}

void UCQuickConsumable_Staff::End_Consum()
{
	bConsuming = false;
	UpdateConsumActor();
}


void UCQuickConsumable_Staff::UpdateConsumActor()
{
	CheckTrue(bConsuming);

	if (!!Consumable)
	{
		CheckTrue(InputItem == Consumable->GetItem());

		// 사용아이템 교체를 위해 기존 사용아이템 삭제
		Consumable->End_Consum.RemoveDynamic(this, &UCQuickConsumable_Staff::End_Consum);
		Consumable->Begin_Consum.RemoveDynamic(this, &UCQuickConsumable_Staff::Begin_Consum);
		Consumable->Destroy();
	}

	if (InputItem == nullptr)
	{
		Consumable = nullptr;
		return;
	}

	const FConsumableDesc* desc = InputItem->GetConsumableDesc();
	TSubclassOf<ACConsumableActor> consumableClass = desc->ConsumableClass;
	if (!!consumableClass == false)
	{
		consumableClass = ACConsumableActor::StaticClass();
	}

	FTransform transform;
	ACConsumableActor* consumable =
		OwnerActor->GetWorld()->SpawnActorDeferred<ACConsumableActor>(consumableClass, transform, OwnerActor);
	consumable->SetData(InputItem, desc);
	UGameplayStatics::FinishSpawningActor(consumable, transform);
	
	Consumable = consumable;
	Consumable->Begin_Consum.AddDynamic(this, &UCQuickConsumable_Staff::Begin_Consum);
	Consumable->End_Consum.AddDynamic(this, &UCQuickConsumable_Staff::End_Consum);

}

void UCQuickConsumable_Staff::OnStockChanged(UCInventoryItem_Consumable* InConsumable, int32 InStock)
{
	if (InStock == 0)
	{
		if (InConsumable == Consumable->GetItem())
			SetNullConsumable();

		return;
	}

	Menu->UpdateQuickSlots();
}
