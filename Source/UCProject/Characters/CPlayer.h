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

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

protected: // Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCInteractorComponent* Interactor;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMotionComponent* Motion;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStanceComponent* CStance;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMoveSpeedComponent* MoveSpeed;

	UPROPERTY(VisibleDefaultsOnly)
		class UCEquipmentComponent* Equipment;

	UPROPERTY(VisibleDefaultsOnly)
		class UCQuickConsumableComponent* QuickConsumable;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTargetingComponent* Targeting;

	UPROPERTY(VisibleDefaultsOnly)
		class UCLiteracyComponent* Literacy;

	UPROPERTY(VisibleDefaultsOnly)
		class UCCommendComponent* Commend;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMenuComponent* Menu;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
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
	void Begin_Idle();
	void Begin_Roll();
	void Begin_Attack();
	void Begin_Take();
	void End_Take();
	void End_Talk();
	void End_Consum();
	void Interact();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void StatusChanged(class UCStatusInstance* InValue);
};
