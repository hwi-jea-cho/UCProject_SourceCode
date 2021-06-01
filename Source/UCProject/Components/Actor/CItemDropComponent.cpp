#include "CItemDropComponent.h"
#include "Global.h"
#include "DataAssets/CDropRateData.h"
#include "Actors/CDropItemActor.h"

UCItemDropComponent::UCItemDropComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Data = nullptr;
}


void UCItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

ACDropItemActor* UCItemDropComponent::SpawnDropItem(FTransform InTransform)
{
	if (!!Data)
		return Data->SpawnRandomDropItem(GetWorld(), InTransform);

	return nullptr;
}

