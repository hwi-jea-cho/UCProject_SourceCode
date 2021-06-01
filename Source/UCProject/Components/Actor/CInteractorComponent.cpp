#include "CInteractorComponent.h"
#include "Global.h"
#include "TableDatas/InteractorDesc.h"


UCInteractorComponent::UCInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CHelpers::GetAsset(&InteractorTable,
		"DataTable'/Game/_MyWorld/DataTables/FInteractorList.FInteractorList'");

}

void UCInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetInteractorID(InteractorID);
}

void UCInteractorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	switch (EndPlayReason)
	{
	case EEndPlayReason::Destroyed: DisableInteraction(); break;
	}
}


void UCInteractorComponent::BeginConnect(AActor* InOtherActor)
{
	CheckTrue(InOtherActor == GetOwner());

	if (!!InOtherActor == false)
	{
		CLog::Print("UCInteractorComponent::BeginConnect Parameter InOtherActor is null");
		return;
	}

	CheckFalse(bActive);
	UCInteractorComponent* other =
		CHelpers::GetComponent<UCInteractorComponent>(InOtherActor);

	CheckFalse(!!other);

	CheckFalse(other->bActive);
	CheckFalse(IsConnectingType(other->InteractorType));
	CheckTrue(Connectings.Contains(other));

	BeginConnected(other);
	other->BeginConnected(this);
}

void UCInteractorComponent::EndConnect(AActor* InOtherActor)
{
	CheckTrue(InOtherActor == GetOwner());

	if (!!InOtherActor == false)
	{
		CLog::Print("UCInteractorComponent::EndConnect Parameter InOtherActor is null");
		return;
	}

	CheckFalse(bActive);
	UCInteractorComponent* other =
		CHelpers::GetComponent<UCInteractorComponent>(InOtherActor);

	CheckFalse(!!other);

	CheckFalse(other->bActive);
	CheckFalse(IsConnectingType(other->InteractorType));
	CheckFalse(Connectings.Contains(other));

	EndConnected(other);
	other->EndConnected(this);
}

void UCInteractorComponent::Interact(UCInteractorComponent* InOther)
{
	CheckFalse(bActive);

	if (OnInteraction.IsBound())
	{
		OnInteraction.Broadcast(InOther);
	}
}


void UCInteractorComponent::DisableInteraction()
{
	CheckFalse(bActive);

	for (UCInteractorComponent* other : Connectings)
	{
		other->EndConnected(this);
	}
	Connectings.Empty();

	bActive = false;
}


void UCInteractorComponent::SetInteractorID(FName InInteractorID)
{
	InteractorID = InInteractorID;


	InteractorName = ConvertIdToName(InInteractorID);
}

void UCInteractorComponent::SetInteractorType(EInteractorType InValue)
{
	InteractorType = InValue; 
}

UCInteractorComponent* UCInteractorComponent::GetLastConnecting() const
{
	uint32 count = Connectings.Num();
	CheckTrueResult(0 == count, nullptr);

	return Connectings[count - 1];
}

FText UCInteractorComponent::ConvertIdToName(FName InId) const
{
	FText result = FText();

	CheckNullResult(InteractorTable, result);

	const FInteractorDesc* desc = nullptr;

	FString ContextString;
	desc = InteractorTable->FindRow<FInteractorDesc>(InId, ContextString);

	if (desc == nullptr)
		return result;

	result = desc->DisplayName;
	return result;
}


// Connectings 리스트에 연결 된 것 추가
void UCInteractorComponent::BeginConnected(UCInteractorComponent* InOther)
{
	Connectings.Add(InOther);

	if (OnInteractorConnected.IsBound())
		OnInteractorConnected.Broadcast(InOther);
}

// Connectings 리스트에 연결 해제 된 것 삭제
void UCInteractorComponent::EndConnected(UCInteractorComponent* InOther)
{
	Connectings.Remove(InOther);

	if (OffInteractorConnected.IsBound())
		OffInteractorConnected.Broadcast(InOther);
}
