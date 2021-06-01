#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TableDatas/ItemDatas.h"
#include "TableDatas/InteractorDesc.h"
#include "CInventoryItem.generated.h"

USTRUCT()
struct FInventoryItemInput
{
	GENERATED_BODY()

public:
	FName ItemID = "None";
	FText DisplayName;
	const FInventoryItemDesc* Desc = nullptr;

};

UCLASS()
class UCPROJECT_API UCInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UCInventoryItem();
	UCInventoryItem* SetData(const FInventoryItemInput& InInput);

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE FName GetItemID() const { return ItemID; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE EItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE FText GetDisplayName() const { return DisplayName; }
	
protected:
	FName ItemID = "None";
	FText DisplayName = FText();
	EItemType ItemType = EItemType::None;
	FText DetailDescription = FText();

	FInventoryItemInput Input;
};
