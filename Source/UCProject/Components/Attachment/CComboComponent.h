#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/CComboData.h"
#include "Actors/CAttackment.h"
#include "CComboComponent.generated.h"

DECLARE_DELEGATE_RetVal(EAttackCommend, FGetNextCommend);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCComboComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<UCComboData*> FirstComboDatas;


public:	
	UCComboComponent();
	void SetFirstCombo(UCComboData* InFirst);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void StartCombo();

private:
	void FinishCombo();
	UFUNCTION()
		void Attack();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class ACAttackment* GetCurrentAttack() const { return CurrCombo; }

public:
	FGetNextCommend GetNextCommend;


private:
	ACAttackment* CurrCombo;
	ACAttackment* FirstAttack;

	class ACAttachment* OwnerWeapon;
	class UCStateComponent* State;

};
