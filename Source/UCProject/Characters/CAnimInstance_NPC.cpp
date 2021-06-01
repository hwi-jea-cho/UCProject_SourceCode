#include "CAnimInstance_NPC.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCAnimInstance_NPC::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Pose = CHelpers::GetComponent<UCNpcPoseComponent>(character);

	PrevHoz = Hoz;
	PrevVert = Vert;
}

void UCAnimInstance_NPC::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	UCharacterMovementComponent* movement = character->GetCharacterMovement();
	IsFalling = movement->IsFalling();

	if (!!Pose)
	{
		CurrPose = Pose->GetPose();

		float maxRotationDelta = RotationSpeed * DeltaSeconds;
		FRotator lookingAt = Pose->GetLookingAtRotation();

		float newHoz = AdjustmentAngle(maxRotationDelta, PrevHoz, lookingAt.Yaw);
		PrevHoz = Hoz;
		Hoz = newHoz;

		float newVert = AdjustmentAngle(maxRotationDelta, PrevVert, lookingAt.Pitch);
		PrevVert = Vert;
		Vert = newVert;
	}

}

float UCAnimInstance_NPC::AdjustmentAngle(float InMaxDelta, float InOldAngle, float InNewAngle)
{
	float result;

	// 0-90, 270-360
	if (InNewAngle <= 90.0f)
		result = InNewAngle;
	else if (InNewAngle >= 270)
		result = InNewAngle - 360.0f;
	else
		result = 0.0f;

	float dest = result - InOldAngle;
	if (dest > InMaxDelta)
		result = InOldAngle + InMaxDelta;
	else if (dest < -InMaxDelta)
		result = InOldAngle - InMaxDelta;

	return result;
}
