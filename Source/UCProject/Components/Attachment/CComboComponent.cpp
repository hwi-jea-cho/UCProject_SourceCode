#include "CComboComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Character/CStateComponent.h"
#include "Actors/CAttachment.h"

UCComboComponent::UCComboComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCComboComponent::SetFirstCombo(UCComboData* InFirst)
{
	if (!!FirstAttack)
		FirstAttack->Destroy();

	FirstAttack = InFirst->Spawn(Cast<ACAttachment>(GetOwner()));
}

void UCComboComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerWeapon = Cast<ACAttachment>(GetOwner());
	ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerWeapon->GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}

void UCComboComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	FirstAttack->Destroy();
}


void UCComboComponent::StartCombo()
{
	CheckFalse(State->IsCanAttack());

	OwnerWeapon->Equip();
	State->SetAttackMode();

	Attack();
}


void UCComboComponent::FinishCombo()
{
	if (!!CurrCombo)
		CurrCombo->OnAttacked.Unbind();

	CurrCombo = nullptr;

	OwnerWeapon->Unequip();
	State->SetIdleMode();
}

// CurrCombo -> OnAttacked
void UCComboComponent::Attack()
{
	CheckFalse(State->IsAttackMode());

	EAttackCommend commend = EAttackCommend::None;
	if (GetNextCommend.IsBound())
	{
		commend = GetNextCommend.Execute();
	}

	ACAttackment* nextCombo;
	if (!!CurrCombo)
		nextCombo = CurrCombo->GetNextCombo(commend);
	else
		nextCombo = FirstAttack->GetNextCombo(commend);

	if (!!nextCombo)
	{
		if (!!CurrCombo)
			CurrCombo->OnAttacked.Unbind();

		CurrCombo = nextCombo;

		nextCombo->OnAttacked.BindUFunction(this, "Attack");
		nextCombo->Attack();
	}
	else
	{
		FinishCombo();
	}

}

