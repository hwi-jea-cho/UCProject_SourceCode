#include "CStateComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCStateComponent::UCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMovement = Cast<ACharacter>(GetOwner())->GetCharacterMovement();
}

void UCStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckNull(OwnerMovement);

	if (OwnerMovement->IsFalling() == false)
	{
		bJumpAction = false;
		bJumpAttack = false;
	}
}


void UCStateComponent::SetMove()
{
	bCanMove = true;
}

void UCStateComponent::SetStop()
{
	bCanMove = false;
}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
	bRolling = false;
	bCanMove = true;
}

void UCStateComponent::SetRollMode()
{
	CheckFalse(IsCanRoll());

	bRolling = true;
	bJumpAction = true;
	ChangeType(EStateType::Roll);
}

void UCStateComponent::SetAttackMode()
{
	CheckFalse(IsCanAttack());

	bJumpAttack = true;
	ChangeType(EStateType::Attack);
}

void UCStateComponent::SetTakeMode()
{
	CheckFalse(IsCanTake());

	ChangeType(EStateType::Take);
}

void UCStateComponent::SetConsumMode()
{
	CheckFalse(IsCanConsum());

	ChangeType(EStateType::Consum);
}

void UCStateComponent::SetTalkMode()
{
	CheckFalse(IsCanTalk());

	SetStop();
	ChangeType(EStateType::Talk);
}


bool UCStateComponent::IsCanMove() const
{
	return (bCanMove);
}

bool UCStateComponent::IsCanOtherMontage() const
{
	return (IsIdleMode());
}

bool UCStateComponent::IsCanRoll() const
{
	return (IsIdleMode()) && (!bRolling) && (!bJumpAction);
}

bool UCStateComponent::IsCanAttack() const
{
	return (IsIdleMode()) && (!bJumpAction) && (!bJumpAttack);
}

bool UCStateComponent::IsCanTake() const
{
	return (IsIdleMode()) && (OwnerMovement->IsFalling() == false);
}

bool UCStateComponent::IsCanConsum() const
{
	return (IsIdleMode()) && (OwnerMovement->IsFalling() == false);
}

bool UCStateComponent::IsCanTalk() const
{
	return (IsIdleMode()) && (OwnerMovement->IsFalling() == false);
}


void UCStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prevType = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(prevType, InNewType);
	}

}
