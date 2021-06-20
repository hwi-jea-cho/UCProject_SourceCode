#include "CAnimNotify_Attacked.h"
#include "Global.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Components/Attachment/CComboComponent.h"
#include "Actors/CAttackment.h"
#include "Actors/CAttachment.h"

FString UCAnimNotify_Attacked::GetNotifyName_Implementation() const
{
	return "Attacked";
}

void UCAnimNotify_Attacked::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	// ���
	UCEquipmentComponent* equipment =
		CHelpers::GetComponent<UCEquipmentComponent>(MeshComp->GetOwner());
	CheckNull(equipment);

	// ����
	ACAttachment* weapon = equipment->GetEquipedWeapon();
	CheckNull(weapon);

	// �޺�
	UCComboComponent* combo =
		CHelpers::GetComponent<UCComboComponent>(weapon);
	CheckNull(combo);

	// ����
	ACAttackment* attackment = combo->GetCurrentAttack();
	CheckNull(attackment);

	attackment->Attacked();
}
