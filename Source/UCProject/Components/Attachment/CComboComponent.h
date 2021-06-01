#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/CComboData.h"
#include "CComboComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCComboComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<UCComboData*> FirstComboDatas;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class ACAttackment* GetCurrentAttack() const { return ComboCurr; }


public:	
	UCComboComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void SetFirstCombo(UCComboData* InFirst);
	bool IsVialdCommend(EAttackCommend InCommend);
	void SetAttackMode(EAttackCommend InCommend);
	void ResetCombo();

private:
	ACAttackment* ComboCurr;
	ACAttackment* FirstAttack;
};
