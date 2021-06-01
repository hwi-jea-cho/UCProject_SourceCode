#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CStatusInstance.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Status")
		FStatusData Status;

public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetLocalStatus(FStatusData InStatus);
	void AddChild(UCStatusInstance* InInstance);

	UFUNCTION()
		void StatusChanged(UCStatusInstance* InValue);

public:
	FORCEINLINE FStatusData GetLocalStatus() const { return Status; }
	FORCEINLINE float GetMoveSpeed() const { return Instance->GetMoveSpeed(); }
	FORCEINLINE float GetHp() const { return Instance->GetHp(); }
	FORCEINLINE float GetAttack() const { return Instance->GetAttack(); }
	FORCEINLINE float GetArmor() const { return Instance->GetArmor(); }

public:
	FStatusChanged OnStatusChanged;

private:
	UPROPERTY()
		UCStatusInstance* Instance;

};
