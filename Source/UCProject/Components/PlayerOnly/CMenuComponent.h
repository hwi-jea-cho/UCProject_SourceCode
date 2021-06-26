#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMenuComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCMenuComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCUserWidget_Menu> MenuClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCUserWidget_Talkable> TalkableClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCUserWidget_QuickSlots> QuickSlotsClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCUserWidget_Interactable> InteractableClass;

public:	
	UCMenuComponent();

protected:
	virtual void BeginPlay() override;

public:
	void OpenMenu();
	void CloseMenu();

	void OpenTalk();
	void SetTalkMent(const FText& InName, const FText& InMent);
	void CloseTalk();

	void UpdateQuickSlots();

private:
	void OpenMenu(class UWidget* InValue);
	void CloseMenu(class UWidget* InValue);
	void VisibleHuds();
	void HiddenHuds();

private:
	class UWidget* OpenedMenu;

	class UCUserWidget_Menu* Menu;
	class UCUserWidget_Talkable* Talkable;
	class UCUserWidget_QuickSlots* QuickSlots;
	class UCUserWidget_Interactable* Interactable;

};
