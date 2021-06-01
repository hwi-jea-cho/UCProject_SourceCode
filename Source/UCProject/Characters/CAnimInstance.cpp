#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	UCStanceComponent* stance =
		CHelpers::GetComponent<UCStanceComponent>(character);
	CheckNull(stance);

	stance->OnStanceChanged.AddDynamic(this, &UCAnimInstance::StanceChanged);
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
}

void UCAnimInstance::StanceChanged(EStanceType InPrevType, EStanceType InNewType)
{
	StanceType = InNewType;
}
