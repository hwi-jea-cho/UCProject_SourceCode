#include "CDropRateData.h"
#include "Global.h"
#include "Actors/CDropItemActor.h"

ACDropItemActor* UCDropRateData::SpawnRandomDropItem(UWorld* InWorld, const FTransform& InTransform)
{
	// ���� ������ ���
	FDropItemData drop;
	CheckFalseResult(GetRandomDropItemClass(&drop), nullptr);

	// ���� ���� ���
	int32 w = drop.ItemCountMax - drop.ItemCountMin;
	int32 itemCount;
	if (w == 0)
	{
		itemCount = drop.ItemCountMax;
	}
	else
	{
		itemCount = FMath::Rand() % w + drop.ItemCountMin;
	}
	CheckTrueResult(itemCount <= 0, nullptr);

	CheckNullResult(drop.DropItemClass, nullptr);

	// ��� ������ ����
	ACDropItemActor* result = InWorld->
		SpawnActorDeferred<ACDropItemActor>
		(
			drop.DropItemClass,
			InTransform
		);
	result->SetData(drop.ItemId, itemCount);
	UGameplayStatics::FinishSpawningActor(result, InTransform);

	return result;
}

bool UCDropRateData::GetRandomDropItemClass(FDropItemData* OutData)
{
	float TotalRate = 0;
	if (TotalRate == 0)
	{
		float newTotal = 0;

		for (const FDropListData& rateList : RateLists)
		{
			newTotal += rateList.DropRate;
		}
		for (const FDropItemData& rateItem : RateItems)
		{
			newTotal += rateItem.DropRate;
		}

		newTotal += EmptyRate;
		TotalRate = newTotal;
	}

	float rate = FMath::FRand() * TotalRate;

	float rateCount = 0.0f;

	for (const FDropListData& rateList : RateLists)
	{
		rateCount += rateList.DropRate;
		if (rateCount > rate)
			return rateList.DropList->GetRandomDropItemClass(OutData);
	}
	for (const FDropItemData& rateItem : RateItems)
	{
		rateCount += rateItem.DropRate;
		if (rateCount > rate)
		{
			(*OutData) = rateItem;
			return true;
		}
	}

	return false;
}
