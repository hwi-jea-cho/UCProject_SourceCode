#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Actors/CAttachment.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	equipment->GetEquipedWeapon()->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	equipment->GetEquipedWeapon()->OffCollision();
}