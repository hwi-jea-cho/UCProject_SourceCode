#include "CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Actors/CAttachment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// 장비
	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	// 무기
	ACAttachment* weapon = equipment->GetEquipedAttachment();
	CheckNull(weapon);

	weapon->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// 장비
	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	// 무기
	ACAttachment* weapon = equipment->GetEquipedAttachment();
	CheckNull(weapon);

	weapon->End_Equip();
}


