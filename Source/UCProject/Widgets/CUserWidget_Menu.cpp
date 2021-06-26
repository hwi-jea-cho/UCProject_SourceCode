#include "CUserWidget_Menu.h"
#include "Global.h"
#include "Components/PlayerOnly/CMenuComponent.h"
#include "Components/PlayerOnly/CInventoryComponent.h"
#include "CUserWidget_Equipment.h"
#include "CUserWidget_Consumable.h"

UCUserWidget_Menu::UCUserWidget_Menu(const FObjectInitializer& InObjectInitializer)
	: UUserWidget(InObjectInitializer)
{
	bIsFocusable = true;
}

void UCUserWidget_Menu::OpenStackable()
{
	SetMenu(EMenuType::Consumable);
}

void UCUserWidget_Menu::OpenEquipment()
{
	SetMenu(EMenuType::Equipment);
}

void UCUserWidget_Menu::OpenNone()
{
	SetMenu(EMenuType::None);
}

void UCUserWidget_Menu::Open()
{
	bOpenedMenu = true;

	Inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwningPlayerPawn());
	OnOpened();
}

void UCUserWidget_Menu::Closs()
{
	SetMenu(EMenuType::None);

	bOpenedMenu = false;
}


FStatusData UCUserWidget_Menu::GetCharacterStatus() const
{
	return Inventory->GetCharacterStatus();
}

void UCUserWidget_Menu::SetMenu(EMenuType InNextMenu)
{
	CheckTrue(currMenu == InNextMenu);

	EMenuType privMenu = currMenu;

	switch (privMenu)
	{
	case EMenuType::Equipment: MenuEquipment->Closs(); break;
	case EMenuType::Consumable: MenuConsumable->Closs(); break;
	}

	currMenu = InNextMenu;

	switch (InNextMenu)
	{
	case EMenuType::Equipment: MenuEquipment->Open(); break;
	case EMenuType::Consumable: MenuConsumable->Open(); break;
	}
}


FReply UCUserWidget_Menu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("Z"))
	{
		UCMenuComponent* menuComponent =
			CHelpers::GetComponent<UCMenuComponent>(GetOwningPlayerPawn());
		
		menuComponent->CloseMenu();
	}
	return FReply::Handled();
}
