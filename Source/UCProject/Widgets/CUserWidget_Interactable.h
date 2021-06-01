#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Interactable.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_Interactable : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCUserWidget_Interactable_Unit> ChildWidgetClass;

public:
	void BeginPlay();
	void UpdateInteractorList();
	
private:
	void SetActivedCount(uint32 InCount);
	class UCUserWidget_Interactable_Unit* CreateChild();

	UFUNCTION()
		void OnInteractorConnected(class UCInteractorComponent* InOther);

	UFUNCTION()
		void OffInteractorConnected(class UCInteractorComponent* InOther);

private:
	class UCInteractorComponent* Interactor;
	uint32 ActivedCount = 0;
	TArray<class UCUserWidget_Interactable_Unit*> Childs;

};
