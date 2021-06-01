#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPlayerMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float RunWeight = 4;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float SprintWeight = 6;

	UPROPERTY(EditAnywhere, Category = "Roll")
		float JumpRollImpulse = -10000;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
		class UAnimMontage* RollingMontage;

public:
	UFUNCTION(BlueprintCallable)
		void ToggleRunMode();
	
	UFUNCTION(BlueprintCallable)
		void SetRunMode();

	UFUNCTION(BlueprintCallable)
		void SetSprintMode();

	UFUNCTION(BlueprintCallable)
		void SetMoveSpeed(float InSpeed);

public:	
	UCPlayerMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	void Begin_Roll(FVector2D InKeyAxis);
	void End_Roll();

private:
	bool ToggleRun = true;
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class UCharacterMovementComponent* CharacterMovement;
};
