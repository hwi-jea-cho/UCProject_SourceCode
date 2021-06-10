#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMoveSpeedComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCMoveSpeedComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Move")
		float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, Category = "Move")
		float RunWeight = 4;

	UPROPERTY(EditAnywhere, Category = "Move")
		float SprintWeight = 6;

public:
	UFUNCTION(BlueprintCallable)
		void SetRunMode();

	UFUNCTION(BlueprintCallable)
		void SetSprintMode();

	UFUNCTION(BlueprintCallable)
		void SetMoveSpeed(float InSpeed);

public:	
	UCMoveSpeedComponent();

protected:
	virtual void BeginPlay() override;

public:
	void ToggleRunMode();

private:
	bool ToggleRun = true;
	class ACharacter* OwnerCharacter;
	class UCharacterMovementComponent* CharacterMovement;

		
};
