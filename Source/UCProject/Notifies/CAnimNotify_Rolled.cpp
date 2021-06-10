#include "CAnimNotify_Rolled.h"
#include "Global.h"
#include "Components/Character/CStateComponent.h"

FString UCAnimNotify_Rolled::GetNotifyName_Implementation() const
{
	return "Rolled";
}

void UCAnimNotify_Rolled::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCStateComponent* state = 
		CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(state);

	state->SetIdleMode();

}
