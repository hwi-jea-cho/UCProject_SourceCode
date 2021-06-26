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

	if (IsGround())
	{
		bCanJumpAction = true;
		bCanJumpAttack = true;
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
	bCanMove = true;
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetAttackMode()
{
	CheckFalse(IsCanAttack());

	bCanJumpAttack = false;
	ChangeType(EStateType::Attack);
}

void UCStateComponent::SetRollMode()
{
	CheckFalse(IsCanRoll());

	bCanJumpAction = false;
	ChangeType(EStateType::Roll);
}

void UCStateComponent::SetTalkMode()
{
	CheckFalse(IsCanTalk());

	SetStop();
	ChangeType(EStateType::Talk);
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


bool UCStateComponent::IsCanMove() const
{
	return (bCanMove);
}

bool UCStateComponent::IsCanIdle() const
{
	return true;
}

bool UCStateComponent::IsCanAttack() const
{
	return IsIdleMode() && bCanJumpAction && bCanJumpAttack;
}

bool UCStateComponent::IsCanRoll() const
{
	return IsIdleMode() && bCanJumpAction;
}

bool UCStateComponent::IsCanTalk() const
{
	return IsIdleMode() && IsGround();
}

bool UCStateComponent::IsCanTake() const
{
	return IsIdleMode() && IsGround();
}

bool UCStateComponent::IsCanConsum() const
{
	return IsIdleMode() && IsGround();
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

bool UCStateComponent::IsGround() const
{
	CheckNullResult(OwnerMovement, true);

	return OwnerMovement->IsFalling() == false;
}
