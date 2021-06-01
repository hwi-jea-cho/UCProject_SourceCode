#include "CNpcPoseComponent.h"
#include "Global.h"

UCNpcPoseComponent::UCNpcPoseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UCNpcPoseComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCNpcPoseComponent::SetLookingAtActor(AActor* InActor)
{
	LookingAtActor = InActor;
}

void UCNpcPoseComponent::UpdatePose()
{
	ChangePose(CurrPose);
}

void UCNpcPoseComponent::ChangePose(ENpcPoseType InNewPose)
{
	ENpcPoseType prevPose = CurrPose;
	CurrPose = InNewPose;

	if (OnPoseChanged.IsBound())
		OnPoseChanged.Broadcast(prevPose, InNewPose);
}

FRotator UCNpcPoseComponent::GetLookingAtRotation() const
{
	FRotator result = FRotator();
	CheckNullResult(LookingAtActor, result);

	FVector src = GetOwner()->GetActorRotation().Vector();
	FVector dest = LookingAtActor->GetActorLocation() - GetOwner()->GetActorLocation();

	result = (dest.ToOrientationRotator() - src.ToOrientationRotator()).Clamp();

	return result;
}

