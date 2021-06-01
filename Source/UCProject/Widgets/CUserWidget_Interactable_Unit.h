#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Interactable_Unit.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_Interactable_Unit : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInteractor(class UCInteractorComponent* InInteractor);
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateName();

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE FText GetInteractorName() const { return InteractorName; }

public:
	FORCEINLINE class UCInteractorComponent* GetInteractor() { return Interactor; }

private:
	FText InteractorName;
	class UCInteractorComponent* Interactor;
};
