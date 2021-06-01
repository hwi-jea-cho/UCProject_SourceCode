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

protected:
	UPROPERTY(BlueprintReadOnly)
		class UCEquipmentComponent* Equipment;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;


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
	class UCComboComponent* CurrCombo;
	class ACAttachment* CurrWeapon;
	EInputCommend InputCommend;
};
