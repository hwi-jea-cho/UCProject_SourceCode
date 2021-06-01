#include "CMenuComponent.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CUserWidget_Menu.h"
#include "Widgets/CUserWidget_Talkable.h"
#include "Widgets/CUserWidget_QuickSlots.h"
#include "Widgets/CUserWidget_Interactable.h"

UCMenuComponent::UCMenuComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CHelpers::GetClass(&MenuClass,
		"WidgetBlueprint'/Game/_MyWorld/Widgets/WB_Menu.WB_Menu_C'");

	CHelpers::GetClass(&TalkableClass,
		"WidgetBlueprint'/Game/_MyWorld/Widgets/WB_Talkable.WB_Talkable_C'");

	CHelpers::GetClass(&QuickSlotsClass,
		"WidgetBlueprint'/Game/_MyWorld/Widgets/WB_QuickSlots.WB_QuickSlots_C'");

	CHelpers::GetClass(&InteractableClass,
		"WidgetBlueprint'/Game/_MyWorld/Widgets/WB_Interactable.WB_Interactable_C'");

}


void UCMenuComponent::BeginPlay()
{
	Super::BeginPlay();

	QuickSlots = CreateWidget<UCUserWidget_QuickSlots>(GetWorld()->GetFirstPlayerController(), QuickSlotsClass);
	QuickSlots->BeginPlay();
	QuickSlots->AddToViewport();
	
	Interactable = CreateWidget<UCUserWidget_Interactable>(GetWorld()->GetFirstPlayerController(), InteractableClass);
	Interactable->BeginPlay();
	Interactable->AddToViewport();

}

void UCMenuComponent::OpenMenu()
{
	CheckTrue(bOpenedMenu);

	APlayerController* playerController =
		GetWorld()->GetFirstPlayerController();

	if (Menu == nullptr)
	{
		Menu = CreateWidget<UCUserWidget_Menu>(playerController, MenuClass);
		Menu->AddToViewport();
	}

	playerController->SetPause(true);
	playerController->SetInputMode(FInputModeUIOnly());
	playerController->bShowMouseCursor = true;
	Menu->SetKeyboardFocus();

	bOpenedMenu = true;
	Menu->Open();
}

void UCMenuComponent::CloseMenu()
{
	Menu->Closs();
	bOpenedMenu = false;

	APlayerController* playerController =
		GetWorld()->GetFirstPlayerController();

	playerController->bShowMouseCursor = false;
	playerController->SetInputMode(FInputModeGameOnly());
	playerController->SetPause(false);

	QuickSlots->UpdateQuickSlots();
}

void UCMenuComponent::OpenTalk()
{
	bOpenedMenu = true;

	Interactable->SetVisibility(ESlateVisibility::Hidden);
	QuickSlots->SetVisibility(ESlateVisibility::Hidden);

	if (Talkable == nullptr)
	{
		APlayerController* playerController =
			GetWorld()->GetFirstPlayerController();

		Talkable = CreateWidget<UCUserWidget_Talkable>(playerController, TalkableClass);
		Talkable->AddToViewport();
	}

	Talkable->SetVisibility(ESlateVisibility::Visible);
}

void UCMenuComponent::SetTalkMent(const FText& InName, const FText& InMent)
{
	Talkable->SetMent(InMent, InName);
}

void UCMenuComponent::CloseTalk()
{
	bOpenedMenu = false;

	Talkable->SetVisibility(ESlateVisibility::Hidden);

	Interactable->SetVisibility(ESlateVisibility::Visible);
	QuickSlots->SetVisibility(ESlateVisibility::Visible);
}


void UCMenuComponent::UpdateQuickSlots()
{
	QuickSlots->UpdateQuickSlots();
}

