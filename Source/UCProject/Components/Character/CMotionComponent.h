#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/MontageDesc.h"
#include "Engine/DataTable.h"
#include "CMotionComponent.generated.h"

UENUM(BlueprintType)
enum class EMotionType : uint8
{
	Dead, Hitted, Roll, Jump, Take, Max
};

USTRUCT(BlueprintType)
struct FMotionDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EMotionType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		class USoundBase* Voice;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCMotionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* MotionTable;

	UPROPERTY(EditAnywhere, Category = "Roll")
		float JumpRollImpulse = -10000;

public:	
	UCMotionComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayDead();
	void PlayHitted();
	void PlayRoll(FVector2D InKeyAxis);
	void PlayJump();

private:
	void PlayAnimMontage(EMotionType InStateType);

private:
	FMotionDesc* Datas[(int32)EMotionType::Max];
		
	class ACharacter* OwnerCharacter;

};
