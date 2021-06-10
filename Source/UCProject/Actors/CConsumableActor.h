#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/CStatusInstance.h"
#include "TableDatas/ConsumableDesc.h"
#include "CConsumableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionComsum);

UCLASS()
class UCPROJECT_API ACConsumableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACConsumableActor();
	void SetData(class UCInventoryItem_Consumable* InItem, const FConsumableDesc* InDesc);

protected:
	virtual void BeginPlay() override;

public:
	void StartConsum();
	void Consum();
	void FinishConsum();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCInventoryItem_Consumable* GetItem() { return Item; }

public:
	UPROPERTY(BlueprintAssignable)
		FActionComsum Begin_Consum;

	UPROPERTY(BlueprintAssignable)
		FActionComsum OnConsum;

	UPROPERTY(BlueprintAssignable)
		FActionComsum End_Consum;

private:
	const FConsumableDesc* Desc;
	class UCInventoryItem_Consumable* Item;
	
	class ACharacter* OwnerCharacter;
	class UCStateComponent* OwnerState;
	class UCQuickConsumableComponent* OwnerComponent;

};
