#include "CCommendComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Character/CEquipmentComponent.h"
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
	Equipment = CHelpers::GetComponent<UCEquipmentComponent>(OwnerCharacter);
	OnChangedWeapon(Equipment->GetEquipedWeapon());
	Equipment->OnChangedWeapon.AddDynamic(this, &UCCommendComponent::OnChangedWeapon);
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
	CheckNull(CurrCombo);

	CurrCombo->StartCombo();
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

	InputCommend = EInputCommend::None;
	return result;
}

// Equipment->OnChangedWeapon
void UCCommendComponent::OnChangedWeapon(ACAttachment* InNewEquipment)
{
	if (!!CurrCombo)
	{
		CurrCombo->GetNextCommend.Unbind();
		CurrCombo = nullptr;
	}

	CurrCombo = CHelpers::GetComponent<UCComboComponent>(InNewEquipment);
	CheckNull(CurrCombo);
	CurrCombo->GetNextCommend.BindUFunction(this, "GetCurrCommend");
}

