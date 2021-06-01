#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/MontageDesc.h"
#include "CComboData.generated.h"

UENUM(BlueprintType)
enum class EAttackCommend : uint8
{
	None, B, Y, JUMP_B, JUMP_Y,
};

USTRUCT(BlueprintType)
struct FAttackmentData : public FMontageDesc
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EAttackCommend Commend;

	UPROPERTY(EditAnywhere)
		bool bCanMove = false;

};


UCLASS()
class UCPROJECT_API UCComboData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttackment> AttackmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FAttackmentData AttackData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<UCComboData*> NextComboDatas;

public:
	class ACAttackment* Spawn(class ACAttachment* InOwnerWeapon);

};
