#include "CTeamComponent.h"

UCTeamComponent::UCTeamComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UCTeamComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCTeamComponent::OnTarget()
{
	if (OnTargetOn.IsBound())
		OnTargetOn.Broadcast();
}

void UCTeamComponent::OffTarget()
{
	if (OffTargetOn.IsBound())
		OffTargetOn.Broadcast();
}

