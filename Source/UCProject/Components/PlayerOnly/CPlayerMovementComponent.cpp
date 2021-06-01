#include "CPlayerMovementComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Character/CStateComponent.h"

UCPlayerMovementComponent::UCPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CHelpers::GetAsset(&RollingMontage,
		"AnimMontage'/Game/_MyWorld/Animations/Kachujin/Montages/Common/Roll_Montage.Roll_Montage'");
}

void UCPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CharacterMovement = OwnerCharacter->GetCharacterMovement();
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}

void UCPlayerMovementComponent::SetMoveSpeed(float InSpeed)
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


void UCPlayerMovementComponent::ToggleRunMode()
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

void UCPlayerMovementComponent::SetRunMode()
{
	CharacterMovement->MaxWalkSpeed = MoveSpeed * RunWeight;
	ToggleRun = false;
}

void UCPlayerMovementComponent::SetSprintMode()
{
	CharacterMovement->MaxWalkSpeed = MoveSpeed * SprintWeight;
	ToggleRun = true;
}

void UCPlayerMovementComponent::Begin_Roll(FVector2D InKeyAxis)
{
	FVector moveForward = FVector::ZeroVector;
	if (0.0f == InKeyAxis.SizeSquared())
	{
		moveForward = OwnerCharacter->GetActorForwardVector();
	}
	else
	{
		FQuat quat = FQuat(FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0));
		moveForward += quat.GetForwardVector() * InKeyAxis.X;
		moveForward += quat.GetRightVector() * InKeyAxis.Y;
	}

	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(
		FVector(0, 0, 0), moveForward.GetSafeNormal2D()
	);

	OwnerCharacter->SetActorRotation(FRotator(0, newRotator.Yaw, 0));

	FVector velocity = OwnerCharacter->GetVelocity();
	OwnerCharacter->GetCharacterMovement()->Velocity =
		FVector(velocity.X, velocity.Y, 0);
	OwnerCharacter->GetCharacterMovement()->AddImpulse(
		FVector(0, 0, JumpRollImpulse));

	OwnerCharacter->PlayAnimMontage(RollingMontage);
}

void UCPlayerMovementComponent::End_Roll()
{
	State->SetIdleMode();
}
