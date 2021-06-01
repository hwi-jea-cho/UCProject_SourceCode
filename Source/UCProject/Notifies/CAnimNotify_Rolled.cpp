#include "CAnimNotify_Rolled.h"
#include "Global.h"
#include "Components/PlayerOnly/CPlayerMovementComponent.h"

FString UCAnimNotify_Rolled::GetNotifyName_Implementation() const
{
	return "Rolled";
}

void UCAnimNotify_Rolled::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCPlayerMovementComponent* movement =
		CHelpers::GetComponent<UCPlayerMovementComponent>(MeshComp->GetOwner());
	CheckNull(movement);

	movement->End_Roll();

}
