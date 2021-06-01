#include "CStanceComponent.h"
#include "Global.h"


UCStanceComponent::UCStanceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCStanceComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UCStanceComponent::SetUnarmedMode()
{
	ChangeType(EStanceType::Unarmed);
}

void UCStanceComponent::SetOneHandMode()
{
	ChangeType(EStanceType::OneHand);
}

void UCStanceComponent::ChangeType(EStanceType InNewType)
{
	EStanceType prevType = Curr;
	Curr = InNewType;

	if (OnStanceChanged.IsBound())
		OnStanceChanged.Broadcast(prevType, InNewType);
}
