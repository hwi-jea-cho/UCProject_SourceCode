#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Dead, Hitted, Attack, Roll, Talk, Take, Consum, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetMove();
	void SetStop();

	void SetIdleMode();
	void SetAttackMode();
	void SetRollMode();
	void SetTalkMode();
	void SetTakeMode();
	void SetConsumMode();

public:
	UFUNCTION(BlueprintPure)
		bool IsCanMove() const;

	UFUNCTION(BlueprintPure)
		bool IsCanIdle() const;

	UFUNCTION(BlueprintPure)
		bool IsCanAttack() const;

	UFUNCTION(BlueprintPure)
		bool IsCanRoll() const;

	UFUNCTION(BlueprintPure)
		bool IsCanTalk() const;

	UFUNCTION(BlueprintPure)
		bool IsCanTake() const;

	UFUNCTION(BlueprintPure)
		bool IsCanConsum() const;

private:
	void ChangeType(EStateType InNewType);
	bool IsGround() const;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() const { return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() const { return Type == EStateType::Roll; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsAttackMode() const { return Type == EStateType::Attack; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTakeMode() const { return Type == EStateType::Take; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsConsumMode() const { return Type == EStateType::Consum; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTalkMode() const { return Type == EStateType::Talk; }

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;

private:
	class UCharacterMovementComponent* OwnerMovement;
	EStateType Type;
	bool bCanJumpAction = true;
	bool bCanJumpAttack = true;
	bool bCanMove = true;
};
