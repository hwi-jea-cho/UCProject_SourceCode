#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CNpcPoseComponent.generated.h"


UENUM(BlueprintType)
enum class ENpcPoseType : uint8
{
	Default, Pose1,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPoseChanged, ENpcPoseType, InOldPose, ENpcPoseType, InNewPose);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCNpcPoseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCNpcPoseComponent();

private:
	UPROPERTY(EditAnywhere)
		ENpcPoseType CurrPose = ENpcPoseType::Default;

protected:
	virtual void BeginPlay() override;

public:
	void SetLookingAtActor(AActor* InActor);
	UFUNCTION(BlueprintCallable)
		void UpdatePose();

private:
	void ChangePose(ENpcPoseType InNewPose);

public:
	FRotator GetLookingAtRotation() const;
	FORCEINLINE ENpcPoseType GetPose() const { return CurrPose; }

public:
	UPROPERTY(BlueprintAssignable)
		FPoseChanged OnPoseChanged;

private:
	AActor* LookingAtActor;

};
