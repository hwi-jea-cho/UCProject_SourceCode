#include "CComboComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Actors/CAttackment.h"
#include "Actors/CAttachment.h"

UCComboComponent::UCComboComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCComboComponent::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform;
	ACAttackment* Attackment = GetWorld()->SpawnActorDeferred<ACAttackment>(ACAttackment::StaticClass(), transform, GetOwner());
	Attackment->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	UGameplayStatics::FinishSpawningActor(Attackment, transform);
	FirstAttack = Attackment;

	ACAttachment* attachment = Cast<ACAttachment>(GetOwner());
	ACAttackment* naxt;
	for (UCComboData* data : FirstComboDatas)
	{
		if (!!data)
		{
			naxt = data->Spawn(attachment);
			if (!!naxt)
				FirstAttack->AddNaxtCombo(naxt);
		}
	}
}

void UCComboComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FirstAttack->Destroy();
}

void UCComboComponent::SetFirstCombo(UCComboData* InFirst)
{
	FirstAttack->Destroy();
	FirstAttack = InFirst->Spawn(Cast<ACAttachment>(GetOwner()));
}

bool UCComboComponent::IsVialdCommend(EAttackCommend InCommend)
{
	ACAttackment* NextCombo;

	if (!!ComboCurr)
		NextCombo = ComboCurr->GetNextCombo(InCommend);
	else
		NextCombo = FirstAttack->GetNextCombo(InCommend);

	return (!!NextCombo);
}

void UCComboComponent::SetAttackMode(EAttackCommend InCommend)
{
	if (!!ComboCurr)
		ComboCurr = ComboCurr->GetNextCombo(InCommend);
	else
		ComboCurr = FirstAttack->GetNextCombo(InCommend);

	if (!!ComboCurr)
		ComboCurr->Attack();
}

void UCComboComponent::ResetCombo()
{
	ComboCurr = nullptr;
}
