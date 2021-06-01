#include "CUserWidget_Talkable.h"


UCUserWidget_Talkable::UCUserWidget_Talkable(const FObjectInitializer& InObjectInitializer)
	: UUserWidget(InObjectInitializer)
{
	bIsFocusable = false;
}

FReply UCUserWidget_Talkable::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("Z"))
	{
	}
	return FReply::Handled();
}

FReply UCUserWidget_Talkable::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}
