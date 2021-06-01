#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Types/MontageDesc.h"
#include "CWeaponData.generated.h"


USTRUCT(BlueprintType)
struct FAttachmentData
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere)
		FMontageDesc EquipmentMontage;

	UPROPERTY(EditAnywhere)
		FMontageDesc UnequipmentMontage;

};

UCLASS()
class UCPROJECT_API UCWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	class ACAttachment* Spawn(class ACharacter* InOwnerCharacter);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FAttachmentData AttachmentData;

	UPROPERTY(EditDefaultsOnly)
		class UCComboData* FirstCombo;

};
