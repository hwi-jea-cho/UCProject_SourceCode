#include "CWeaponData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Attachment/CComboComponent.h"
#include "Actors/CAttachment.h"
#include "CComboData.h"

ACAttachment* UCWeaponData::Spawn(ACharacter* InOwnerCharacter)
{
	FTransform transform;

	if (!AttachmentClass)
		AttachmentClass = ACAttachment::StaticClass();
	
	ACAttachment* Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
	Attachment->SetData(AttachmentData);
	UGameplayStatics::FinishSpawningActor(Attachment, transform);


	if (!!FirstCombo)
	{
		UCComboComponent* combo = CHelpers::GetComponent<UCComboComponent>(Attachment);
		if (!!combo)
			combo->SetFirstCombo(FirstCombo);

	}

	return Attachment;
}
