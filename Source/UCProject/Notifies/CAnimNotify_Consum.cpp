#include "CAnimNotify_Consum.h"
#include "Global.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"
#include "Actors/CConsumableActor.h"

FString UCAnimNotify_Consum::GetNotifyName_Implementation() const
{
	return "Consum";
}

void UCAnimNotify_Consum::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// QuickItemComponent
	UCQuickConsumableComponent* quickConsumable =
		CHelpers::GetComponent<UCQuickConsumableComponent>(MeshComp->GetOwner());
	CheckNull(quickConsumable);

	ACConsumableActor* actor = quickConsumable->GetCurrActor();

	CheckNull(actor);

	actor->Consum();
}
