#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/CStatusInstance.h"
#include "Components/Character/CStateComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class UCPROJECT_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

		
protected: // Scene Component
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class USpringArmComponent* SpringArm;

private: 
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: // Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStanceComponent* Stance;

	UPROPERTY(VisibleDefaultsOnly)
		class UCPlayerMovementComponent* Movement;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTargetingComponent* Targeting;

	UPROPERTY(VisibleDefaultsOnly)
		class UCCommendComponent* Commend;

	UPROPERTY(VisibleDefaultsOnly)
		class UCLiteracyComponent* Literacy;

	UPROPERTY(VisibleDefaultsOnly)
		class UCEquipmentComponent* Equipment;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInteractorComponent* Interactor;

	UPROPERTY(VisibleDefaultsOnly)
		class UCQuickConsumableComponent* QuickConsumable;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMenuComponent* Menu;


private:
	UPROPERTY(EditAnywhere)
		class USoundBase* JumpVoice;

	UPROPERTY(EditAnywhere)
		FStatusData StatusCharacter;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnTurn(float InAxis);
	void OnLookUp(float InAxis);
	void OnTurnRate(float InAxis);
	void OnLookUpRate(float InAxis);
	void OnZoom(float InAxis);

	void OnRolling();
	void OnJumping();
	void OffJumping();
	void OnToggleRun();
	void OnWeakAttack();
	void OnStrongAttack();
	void OnOpenMenu();
	void OnTargeting();
	void OnTargetLeft();
	void OnTargetRight();
	void OnQuick1();
	void OnQuick2();
	void OnQuick3();
	void OnQuick4();

private:
	void Begin_Roll();
	void Begin_Attack();
	void Begin_Take();
	void End_Take();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void StatusChanged(class UCStatusInstance* InValue);
};
