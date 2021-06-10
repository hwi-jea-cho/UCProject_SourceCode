#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/CComboData.h"
#include "CCommendComponent.generated.h"

UENUM(BlueprintType)
enum class EInputCommend : uint8
{
	None, B, Y,
	MAX
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCCommendComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	UCCommendComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void WeakAttack();
	void StrongAttack();

	void NextCombo();
	void FinishAttack();

private:
	void BeginCombo();
	EAttackCommend GetCurrCommend();
	bool IsVialdCommend(EAttackCommend InCommend);

private:
	class ACharacter* OwnerCharacter;
	class UCEquipmentComponent* Equipment;
	class UCStateComponent* State;

	class ACAttachment* CurrWeapon;
	class UCComboComponent* CurrCombo;

	EInputCommend InputCommend;
};
