#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTargetingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackOnDistance = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LookOnDistance = 1000.0f;

public:
	UFUNCTION(BlueprintCallable)
		void LookOnAttack();

	UFUNCTION(BlueprintCallable)
		void ToggleLookOn();

	UFUNCTION(BlueprintCallable)
		void LookOnLeft();

	UFUNCTION(BlueprintCallable)
		void LookOnRight();

	UFUNCTION(BlueprintCallable)
		void StartLookOn();

	UFUNCTION(BlueprintCallable)
		void EndLookOn();

public:
	UCTargetingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// �÷��̾� ���� ���� ���� ���� ���� ����
	AActor* GetNearbyAttackTarget();
	// ī�޶� ���� ���� ���� ���� ���� ����
	void UpdateLookOnTargets();
	void SetLookOn(AActor* InNewTarget);

private:
	APawn* OwnerPawn;
	AActor* LookOnActor;
	TArray<AActor*> LookOnTargets;

};
