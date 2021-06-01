#include "CDropItemActor.h"
#include "Global.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/PlayerOnly/CInventoryComponent.h"

ACDropItemActor::ACDropItemActor()
{
	// -- CreateComponent Actor -- //
	CHelpers::CreateActorComponent(this, &Interactor, "Interactor");

	Interactor->SetInteractorType(EInteractorType::DropItem);
}

void ACDropItemActor::SetData(FName InItemID, int32 InItemCount)
{
	ItemID = InItemID;
	ItemCount = InItemCount;
	Interactor->SetInteractorID(ItemID);
}

void ACDropItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	Interactor->OnInteraction.AddDynamic(this, &ACDropItemActor::Interaction);
	Interactor->SetInteractorID(ItemID);
}

void ACDropItemActor::Interaction(UCInteractorComponent* InOther)
{
	Destroy();

	CheckFalse(!!InOther);

	AActor* player = InOther->GetOwner();

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(player);
	CheckFalse(!!inventory);

	inventory->AddItem(ItemID, ItemCount);
}


