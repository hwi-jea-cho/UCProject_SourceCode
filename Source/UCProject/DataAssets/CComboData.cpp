#include "CComboData.h"
#include "Global.h"
#include "Actors/CAttachment.h"
#include "Actors/CAttackment.h"

ACAttackment* UCComboData::Spawn(ACAttachment* InOwnerWeapon)
{
	FTransform transform;

	if (!AttackmentClass)
		AttackmentClass = ACAttackment::StaticClass();

	ACAttackment* Attackment = InOwnerWeapon->GetWorld()->SpawnActorDeferred<ACAttackment>(AttackmentClass, transform, InOwnerWeapon);
	Attackment->AttachToComponent(InOwnerWeapon->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Attackment->SetData(AttackData);
	UGameplayStatics::FinishSpawningActor(Attackment, transform);

	for (UCComboData* naxtData : NextComboDatas)
	{
		if (!!naxtData)
		{
			ACAttackment* next = naxtData->Spawn(InOwnerWeapon);

			if (!!next)
			{
				Attackment->AddNaxtCombo(next);
			}

		}
	}
	return Attackment;
}

