#include "CAnimNotify_EndConsum.h"
#include "Global.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"
#include "Actors/CConsumableActor.h"


FString UCAnimNotify_EndConsum::GetNotifyName_Implementation() const
{
	return "EndConsum";
}

void UCAnimNotify_EndConsum::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

	actor->FinishConsum();
}
