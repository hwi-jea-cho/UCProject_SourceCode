#include "CUserWidget_Interactable_Unit.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Actors/CDropItemActor.h"

void UCUserWidget_Interactable_Unit::SetInteractor(UCInteractorComponent* InInteractor)
{
	Interactor = InInteractor;
	InteractorName = Interactor->GetInteractorName();

	if (Interactor->GetInteractorType() == EInteractorType::DropItem)
	{
		ACDropItemActor* item = Cast<ACDropItemActor>(InInteractor->GetOwner());

		if (!!item)
		{
			InteractorName = FText::Format(InteractorName, item->GetItemCount());
		}
	}

	UpdateName();
}
