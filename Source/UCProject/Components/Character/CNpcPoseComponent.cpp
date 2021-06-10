#include "CNpcPoseComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"


UCNpcPoseComponent::UCNpcPoseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCNpcPoseComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	if (!!ownerCharacter)
	{
		OwnerMesh = ownerCharacter->GetMesh();

	}

	SetPose(StartPoseName);
}


void UCNpcPoseComponent::SetPose(FName InNewPose)
{
	CheckNull(OwnerMesh);
	CheckNull(PoseTable);

	const FNpcPoseDesc* poseDesc = nullptr;

	FString contextString;
	poseDesc = PoseTable->FindRow<FNpcPoseDesc>(InNewPose, contextString);

	CheckNull(poseDesc);
	CheckNull(poseDesc->AnimClass);

	OwnerMesh->SetAnimInstanceClass(poseDesc->AnimClass);

}



