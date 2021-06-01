#include "CAnimNotify_EndConsum.h"
#include "Global.h"
#include "Types/CQuickConsumable_Staff.h"
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

	UCQuickConsumable_Staff* staff = quickConsumable->GetCurrConsum();

	CheckNull(staff);

	ACConsumableActor* actor = staff->GetItemActor();

	CheckNull(actor);

	actor->FinishConsum();
}
