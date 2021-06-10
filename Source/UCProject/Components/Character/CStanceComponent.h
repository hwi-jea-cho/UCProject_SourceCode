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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangedStance, EStanceType, InPrevType, EStanceType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangedHeadRotation, FRotator, InRotator);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCStanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStanceComponent();


protected:
	virtual void BeginPlay() override;

public:
	void SetUnarmedMode();
	void SetOneHandMode();

	void SetHeadRotation(const FRotator& InRotator);


private:
	void ChangeType(EStanceType InNewType);


public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() const { return Curr == EStanceType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandMode() const { return Curr == EStanceType::OneHand; }


public:
	UPROPERTY(BlueprintAssignable)
		FChangedStance OnChangedStance;

	UPROPERTY(BlueprintAssignable)
		FChangedHeadRotation OnChangedHeadRotation;


private:
	EStanceType Curr;

};
