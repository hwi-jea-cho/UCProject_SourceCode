#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStanceComponent.generated.h"

UENUM(BlueprintType)
enum class EStanceType : uint8
{
	Unarmed, OneHand,
	Max
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStanceChanged, EStanceType, InPrevType, EStanceType, InNewType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCStanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStanceComponent();

public:
	void SetUnarmedMode();
	void SetOneHandMode();

private:
	void ChangeType(EStanceType InNewType);

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() const { return Curr == EStanceType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() const { return Curr == EStanceType::OneHand; }

public:
	UPROPERTY(BlueprintAssignable)
		FStanceChanged OnStanceChanged;

private:
	EStanceType Curr;
};
