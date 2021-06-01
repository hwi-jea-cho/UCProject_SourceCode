#include "CStatusComponent.h"

UCStatusComponent::UCStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Instance = NewObject<UCStatusInstance>();
	Instance->SetLocalData(Status);

	Instance->OnStatusChanged.AddDynamic(this, &UCStatusComponent::StatusChanged);
}

void UCStatusComponent::SetLocalStatus(FStatusData InStatus)
{
	Status = InStatus;

	if (!!Instance)
		Instance->SetLocalData(Status);
}

void UCStatusComponent::AddChild(UCStatusInstance* InInstance)
{
	InInstance->SetParent(Instance);
}

void UCStatusComponent::StatusChanged(UCStatusInstance* InValue)
{
	if (OnStatusChanged.IsBound())
		OnStatusChanged.Broadcast(InValue);

}
