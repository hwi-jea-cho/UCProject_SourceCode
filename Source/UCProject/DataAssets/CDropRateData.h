#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "CDropRateData.generated.h"

USTRUCT(BlueprintType)
struct FDropItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName ItemId;

	UPROPERTY(EditAnywhere)
		int32 ItemCountMin = 1;

	UPROPERTY(EditAnywhere)
		int32 ItemCountMax = 1;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACDropItemActor> DropItemClass;

	UPROPERTY(EditAnywhere)
		float DropRate;
};

USTRUCT(BlueprintType)
struct FDropListData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UCDropRateData* DropList;

	UPROPERTY(EditAnywhere)
		float DropRate;
};


UCLASS()
class UCPROJECT_API UCDropRateData : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		TArray<FDropListData> RateLists;

	UPROPERTY(EditAnywhere)
		TArray<FDropItemData> RateItems;

	UPROPERTY(EditAnywhere)
		float EmptyRate = 0;

public:
	class ACDropItemActor* SpawnRandomDropItem(UWorld* InWorld, const FTransform& InTransform);
	bool GetRandomDropItemClass(FDropItemData* OutData);

};
