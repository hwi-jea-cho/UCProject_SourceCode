#include "CMotionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UCMotionComponent::UCMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CHelpers::GetAsset(&MotionTable,
		"DataTable'/Game/_MyWorld/DataTables/Player/FPlayerMotionList.FPlayerMotionList'");
	
}

void UCMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<FMotionDesc*> datas;

	FString contextString;
	MotionTable->GetAllRows<FMotionDesc>(contextString, datas);

	for (int32 i = 0; i < (int32)EMotionType::Max; i++)
	{
		for (FMotionDesc* data : datas)
		{
			if ((EMotionType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}
	}
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());

}


void UCMotionComponent::PlayDead()
{
	PlayAnimMontage(EMotionType::Dead);
}

void UCMotionComponent::PlayHitted()
{
	PlayAnimMontage(EMotionType::Hitted);
}

void UCMotionComponent::PlayRoll(FVector2D InKeyAxis)
{
	// 구르기 방향 조절
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

	// 점프 중일 때 빠른 착지
	FVector velocity = OwnerCharacter->GetVelocity();
	OwnerCharacter->GetCharacterMovement()->Velocity =
		FVector(velocity.X, velocity.Y, 0);
	OwnerCharacter->GetCharacterMovement()->AddImpulse(
		FVector(0, 0, JumpRollImpulse));

	PlayAnimMontage(EMotionType::Roll);
}

void UCMotionComponent::PlayJump()
{
	OwnerCharacter->Jump();
	PlayAnimMontage(EMotionType::Jump);
}


void UCMotionComponent::PlayAnimMontage(EMotionType InStateType)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FMotionDesc* data = Datas[(int32)InStateType];
	if (!!data)
	{
		if (!!data->AnimMontage)
		{
			character->PlayAnimMontage(
				data->AnimMontage, data->PlayRatio, data->StartSection
			);
		}

		if (!!data->Voice)
		{
			UGameplayStatics::SpawnSoundAtLocation(
				GetWorld(), data->Voice, OwnerCharacter->GetActorLocation()
			);
		}

	}

}
