#include "CCommendComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Components/Character/CStateComponent.h"
#include "Components/Attachment/CComboComponent.h"
#include "Actors/CAttachment.h"

UCCommendComponent::UCCommendComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCCommendComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Equipment = CHelpers::GetComponent<UCEquipmentComponent>(OwnerCharacter);
}

// Player
void UCCommendComponent::WeakAttack()
{
	InputCommend = EInputCommend::B;
	BeginCombo();
}

// Player
void UCCommendComponent::StrongAttack()
{
	InputCommend = EInputCommend::Y;
	BeginCombo();
}


// Private
void UCCommendComponent::BeginCombo()
{
	CheckFalse(State->IsCanAttack());

	CurrWeapon = Equipment->GetEquipedAttachment();
	CheckFalse(!!CurrWeapon);

	CurrCombo = CHelpers::GetComponent<UCComboComponent>(CurrWeapon);
	EAttackCommend curr = GetCurrCommend();

	if (IsVialdCommend(curr))
	{
		CurrCombo->SetAttackMode(curr);
		CurrWeapon->Equip();
		State->SetAttackMode();
	}

	InputCommend = EInputCommend::None;
}

// Notify
void UCCommendComponent::NextCombo()
{
	EAttackCommend curr = GetCurrCommend();
	if (IsVialdCommend(curr))
	{
		CurrCombo->SetAttackMode(curr);
		InputCommend = EInputCommend::None;
	}
	else
	{
		FinishAttack();
	}
}

// None
void UCCommendComponent::FinishAttack()
{
	CurrCombo->ResetCombo();
	CurrWeapon->Unequip();
	State->SetIdleMode();

	InputCommend = EInputCommend::None;
}


// Private
EAttackCommend UCCommendComponent::GetCurrCommend()
{
	EAttackCommend result = EAttackCommend::None;

	if (OwnerCharacter->GetCharacterMovement()->IsFalling())
	{
		switch (InputCommend)
		{
		case EInputCommend::B: result = EAttackCommend::JUMP_B; break;
		case EInputCommend::Y: result = EAttackCommend::JUMP_Y; break;
		}
	}
	else
	{
		switch (InputCommend)
		{
		case EInputCommend::B: result = EAttackCommend::B; break;
		case EInputCommend::Y: result = EAttackCommend::Y; break;
		}
	}

	return result;
}

// Private
bool UCCommendComponent::IsVialdCommend(EAttackCommend InCommend)
{
	CheckFalseResult(!!CurrCombo, false);

	return CurrCombo->IsVialdCommend(InCommend);
}

