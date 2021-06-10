#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CQuickConsumableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCQuickConsumableComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	UCQuickConsumableComponent();

protected:
	virtual void BeginPlay() override;

public:
	void OnQuick1();
	void OnQuick2();
	void OnQuick3();
	void OnQuick4();
	void SetNullItemQuick1();
	void SetNullItemQuick2();
	void SetNullItemQuick3();
	void SetNullItemQuick4();
	void SetItemQuick1(class UCInventoryItem_Consumable* InConsumable);
	void SetItemQuick2(class UCInventoryItem_Consumable* InConsumable);
	void SetItemQuick3(class UCInventoryItem_Consumable* InConsumable);
	void SetItemQuick4(class UCInventoryItem_Consumable* InConsumable);
	class UCInventoryItem_Consumable* GetItemQuick1();
	class UCInventoryItem_Consumable* GetItemQuick2();
	class UCInventoryItem_Consumable* GetItemQuick3();
	class UCInventoryItem_Consumable* GetItemQuick4();

	// ACConsumableActor
	void SetCurrActor(class ACConsumableActor* InConsumable);
	void SetCurrActorNull();

private:
	void SetNullItemQuick(class UCQuickConsumable_Staff* InQuick);
	void SetItemQuick(class UCQuickConsumable_Staff* InQuick, class UCInventoryItem_Consumable* InConsumable);
	void StartConsum_Staff(class UCQuickConsumable_Staff* InStaff);

public:
	FORCEINLINE class ACConsumableActor* GetCurrActor() { return CurrQuickActor; }

private:
	UPROPERTY()
		class UCQuickConsumable_Staff* QuickSlot1;
	UPROPERTY()
		class UCQuickConsumable_Staff* QuickSlot2;
	UPROPERTY()
		class UCQuickConsumable_Staff* QuickSlot3;
	UPROPERTY()
		class UCQuickConsumable_Staff* QuickSlot4;

	class ACConsumableActor* CurrQuickActor;
	class UCStateComponent* State;

};
