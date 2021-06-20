#include "CAnimNotifyState_Unequip.h"
#include "Global.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Actors/CAttachment.h"

FString UCAnimNotifyState_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}

void UCAnimNotifyState_Unequip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// 장비
	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	// 무기
	ACAttachment* weapon = equipment->GetEquipedWeapon();
	CheckNull(weapon);

	weapon->Begin_Unequip();
}

void UCAnimNotifyState_Unequip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// 장비
	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	// 무기
	ACAttachment* weapon = equipment->GetEquipedWeapon();
	CheckNull(weapon);

	weapon->End_Unequip();
}


