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
		float newHoz = AdjustmentAngle(maxRotationDelta, PrevHoz, TargetHoz);
		PrevHoz = HeadHoz;
		HeadHoz = newHoz;
	}

	if (TargetVert != PrevVert)
	{
		float newVert = AdjustmentAngle(maxRotationDelta, PrevVert, TargetVert);
		PrevVert = HeadVert;
		HeadVert = newVert;
	}
}

float UCAnimInstance::AdjustmentAngle(float InMaxDelta, float InOldAngle, float InNewAngle)
{
	float result;

	// 각도 변환
	// 0~90, 270~360 -> -90~90
	if (InNewAngle <= 90.0f)
		result = InNewAngle;
	else if (InNewAngle >= 270)
		result = InNewAngle - 360.0f;
	else
		result = 0.0f;

	// 최대 회전 크기까지 만큼 회전
	float dest = result - InOldAngle;
	if (dest > InMaxDelta)
		result = InOldAngle + InMaxDelta;
	else if (dest < -InMaxDelta)
		result = InOldAngle - InMaxDelta;

	return result;
}


void UCAnimInstance::OnChangedStance(EStanceType InPrevType, EStanceType InNewType)
{
	StanceType = InNewType;
}

void UCAnimInstance::OnChangedHeadRotation(FRotator InRotator)
{
	TargetHoz = InRotator.Yaw;
	TargetVert = InRotator.Pitch;
}
