#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAssets/CComboData.h"
#include "CAttackment.generated.h"

UCLASS()
class UCPROJECT_API ACAttackment : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACAttachment* OwnerWeapon;

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCCommendComponent* Commend;


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


public:
	// 몽타쥬 실행
	UFUNCTION(BlueprintNativeEvent)
		void Attack();
	void Attack_Implementation();

	// 공격 종료 애님 노티파이
	UFUNCTION(BlueprintNativeEvent)
		void OnAttacked();
	void OnAttacked_Implementation();


private:
	FAttackmentData Data;
	TArray<ACAttackment*> NextCombos;

};
