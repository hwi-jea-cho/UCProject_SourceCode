#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInteractorComponent.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumAluesAsMaskValueslnEditor = "true"))
enum class EInteractorType : uint8
{
	Default		= 0, 
	Player		= 1,
	DropItem	= 2, 
	Chest		= 3,
	NPC			= 4,
};
ENUM_CLASS_FLAGS(EInteractorType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteraction, class UCInteractorComponent*, InOther);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactor", meta = (Bitmask, BitmaskEnum = EInteractorType))
		int32 ConnectingTypes = (int32)(1u << (uint8)EInteractorType::Player);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interactor")
		class UDataTable* InteractorTable;

	UPROPERTY(EditAnywhere, Category = "Interactor")
		EInteractorType InteractorType = EInteractorType::Default;

	UPROPERTY(EditAnywhere, Category = "Interactor")
		FName InteractorID = L"Default";

public:
	UCInteractorComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	UFUNCTION(BlueprintCallable)
		void BeginConnect(AActor* InOtherActor);

	UFUNCTION(BlueprintCallable)
		void EndConnect(AActor* InOtherActor);

	UFUNCTION(BlueprintCallable)
		void Interact(UCInteractorComponent* InOther);

	UFUNCTION(BlueprintCallable)
		void DisableInteraction();

public:
	void SetInteractorID(FName InInteractorID);
	void SetInteractorType(EInteractorType InValue);
	UCInteractorComponent* GetLastConnecting() const;
	FText ConvertIdToName(FName InId) const;

private:
	void BeginConnected(UCInteractorComponent* InOther);
	void EndConnected(UCInteractorComponent* InOther);

public:
	FORCEINLINE FName GetInteractorID() const { return InteractorID; }
	FORCEINLINE FText GetInteractorName() const { return InteractorName; }
	FORCEINLINE EInteractorType GetInteractorType() const { return InteractorType; }
	FORCEINLINE uint32 GetConnectingCount() const { return Connectings.Num(); }
	FORCEINLINE UCInteractorComponent* GetConnecting(uint32 InIndex) { return Connectings[InIndex]; }
	FORCEINLINE bool IsConnectingType(EInteractorType InValue) const { return ((uint32)ConnectingTypes & (1u << (uint32)InValue)) == 0 ? false : true; }

public:
	UPROPERTY(BlueprintAssignable)
		FInteraction OnInteractorConnected;

	UPROPERTY(BlueprintAssignable)
		FInteraction OffInteractorConnected;

	UPROPERTY(BlueprintAssignable)
		FInteraction OnInteraction;

private:
	bool bActive = true;
	FText InteractorName;
	TArray<UCInteractorComponent*> Connectings;

};
