#include "CUserWidget_Interactable.h"
#include "Global.h"
#include "Components/VerticalBox.h"
#include "Components/Actor/CInteractorComponent.h"
#include "CUserWidget_Interactable_Unit.h"


void UCUserWidget_Interactable::BeginPlay()
{
	AActor* Player = GetOwningPlayerPawn();
	Interactor = CHelpers::GetComponent<UCInteractorComponent>(Player);

	Interactor->OnInteractorConnected.AddDynamic(this, &UCUserWidget_Interactable::OnInteractorConnected);
	Interactor->OffInteractorConnected.AddDynamic(this, &UCUserWidget_Interactable::OffInteractorConnected);

	UpdateInteractorList();
}

void UCUserWidget_Interactable::UpdateInteractorList()
{
	uint32 size = Interactor->GetConnectingCount();

	SetActivedCount(size);

	for (uint32 i = 0; i < size; i++)
		Childs[i]->SetInteractor(Interactor->GetConnecting(i));
}

// 오브젝트 풀링
void UCUserWidget_Interactable::SetActivedCount(uint32 InCount)
{
	if (ActivedCount < InCount)
	{
		uint32 childCount = Childs.Num();

		if (childCount < InCount)
		{
			for (uint32 i = childCount; i < InCount; i++)
			{
				CreateChild();
			}
		}

		for (uint32 i = ActivedCount; i < InCount; i++)
			Childs[i]->SetVisibility(ESlateVisibility::Visible);
	}
	else if (InCount < ActivedCount)
	{
		for (uint32 i = InCount; i < ActivedCount; i++)
			Childs[i]->SetVisibility(ESlateVisibility::Hidden);

	}

	ActivedCount = InCount;
}

UCUserWidget_Interactable_Unit* UCUserWidget_Interactable::CreateChild()
{
	UCUserWidget_Interactable_Unit* result 
		= Cast<UCUserWidget_Interactable_Unit>(CreateWidget(this, ChildWidgetClass));

	result->SetVisibility(ESlateVisibility::Hidden);

	VerticalBox->AddChildToVerticalBox(result);

	Childs.Add(result);

	return result;
}


void UCUserWidget_Interactable::OnInteractorConnected(UCInteractorComponent* InOther)
{
	UpdateInteractorList();
}

void UCUserWidget_Interactable::OffInteractorConnected(UCInteractorComponent* InOther)
{
	UpdateInteractorList();
}
