#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAssets/CComboData.h"
#include "CAttackment.generated.h"

DECLARE_DELEGATE(FAttackedAttackment);

UCLASS()
class UCPROJECT_API ACAttackment : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACAttachment* OwnerWeapon;

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;


public:	
	ACAttackment();
	void SetData(FAttackmentData InData);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	bool IsVialdCommend(EAttackCommend InCommend);
	ACAttackment* GetNextCombo(EAttackCommend InCommend);
	void AddNaxtCombo(ACAttackment* InNext);
	void ReverseSpawnNaxtCombos();
	void TakeDamage_Attackment(AActor* InAttackerCauser, AActor* InAttackTarget);


public:
	// ¸ùÅ¸Áê ½ÇÇà
	UFUNCTION(BlueprintNativeEvent)
		void Attack();
	void Attack_Implementation();

	// °ø°Ý Á¾·á ¾Ö´Ô ³ëÆ¼ÆÄÀÌ
	UFUNCTION(BlueprintNativeEvent)
		void Attacked();
	void Attacked_Implementation();

public:
	FAttackedAttackment OnAttacked;

private:
	class UCStateComponent* State;
	class UCComboComponent* Combo;
	class UCTeamComponent* AttackTarget;

	FAttackmentData Data;
	TArray<ACAttackment*> NextCombos;
};
