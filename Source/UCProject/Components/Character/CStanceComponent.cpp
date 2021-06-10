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

void UCStanceComponent::SetHeadRotation(const FRotator& InRotator)
{
	if (OnChangedHeadRotation.IsBound())
		OnChangedHeadRotation.Broadcast(InRotator);
}


void UCStanceComponent::ChangeType(EStanceType InNewType)
{
	EStanceType prevType = Curr;
	Curr = InNewType;

	if (OnChangedStance.IsBound())
		OnChangedStance.Broadcast(prevType, InNewType);
}
