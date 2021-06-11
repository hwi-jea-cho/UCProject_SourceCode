#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PrevHoz = HeadHoz;
	PrevVert = HeadVert;

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	UCStanceComponent* stance =
		CHelpers::GetComponent<UCStanceComponent>(character);
	CheckNull(stance);

	stance->OnChangedStance.AddDynamic(this, &UCAnimInstance::OnChangedStance);
	stance->OnChangedHeadRotation.AddDynamic(this, &UCAnimInstance::OnChangedHeadRotation);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	UCharacterMovementComponent* movement = character->GetCharacterMovement();
	IsFalling = movement->IsFalling();
	IsCrouching = movement->IsCrouching();

	float maxRotationDelta = HeadSpeed * DeltaSeconds;

	if (TargetHoz != PrevHoz)
	{
		PrevHoz = HeadHoz;
		HeadHoz = AdjustmentAngle(maxRotationDelta, HeadHoz, TargetHoz);
	}

	if (TargetVert != PrevVert)
	{
		PrevVert = HeadVert;
		HeadVert = AdjustmentAngle(maxRotationDelta, HeadVert, TargetVert);
	}
}

float UCAnimInstance::AdjustmentAngle(float InMaxDelta, float InOldAngle, float InNewAngle)
{
	// 최대 회전 크기까지 만큼 회전
	float dest = InNewAngle - InOldAngle;

	if (dest > InMaxDelta)
		return InOldAngle + InMaxDelta;

	if (dest < -InMaxDelta)
		return InOldAngle - InMaxDelta;

	return InNewAngle;
}


void UCAnimInstance::OnChangedStance(EStanceType InPrevType, EStanceType InNewType)
{
	StanceType = InNewType;
}

void UCAnimInstance::OnChangedHeadRotation(FRotator InRotator)
{
	InRotator = InRotator.Vector().ToOrientationRotator();

	TargetHoz = InRotator.Yaw;
	TargetVert = InRotator.Pitch;

}
