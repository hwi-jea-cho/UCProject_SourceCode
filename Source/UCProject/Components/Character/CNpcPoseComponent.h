#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CNpcPoseComponent.generated.h"

USTRUCT(BlueprintType)
struct FNpcPoseDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UAnimInstance> AnimClass;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCNpcPoseComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* PoseTable;

	UPROPERTY(EditAnywhere, Category = "NpcPose")
		FName StartPoseName;

public:
	UCNpcPoseComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void SetPose(FName InNewPose);

private:
	class USkeletalMeshComponent* OwnerMesh;

};
