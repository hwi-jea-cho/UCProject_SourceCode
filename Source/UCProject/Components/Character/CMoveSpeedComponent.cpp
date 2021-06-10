#include "CMoveSpeedComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Character/CStateComponent.h"


UCMoveSpeedComponent::UCMoveSpeedComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCMoveSpeedComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CharacterMovement = OwnerCharacter->GetCharacterMovement();
}


void UCMoveSpeedComponent::SetRunMode()
{
	CharacterMovement->MaxWalkSpeed = MoveSpeed * RunWeight;
	ToggleRun = false;
}

void UCMoveSpeedComponent::SetSprintMode()
{
	CharacterMovement->MaxWalkSpeed = MoveSpeed * SprintWeight;
	ToggleRun = true;
}


void UCMoveSpeedComponent::SetMoveSpeed(float InSpeed)
{
	MoveSpeed = InSpeed;

	CheckNull(CharacterMovement);

	if (ToggleRun)
	{
		CharacterMovement->MaxWalkSpeed = MoveSpeed * SprintWeight;
	}
	else
	{
		CharacterMovement->MaxWalkSpeed = MoveSpeed * RunWeight;
	}
}


void UCMoveSpeedComponent::ToggleRunMode()
{
	if (ToggleRun)
	{
		SetRunMode();
	}
	else
	{
		SetSprintMode();
	}
}
