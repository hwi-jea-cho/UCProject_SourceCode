#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Talkable.generated.h"

UCLASS()
class UCPROJECT_API UCUserWidget_Talkable : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCUserWidget_Talkable(const FObjectInitializer& InObjectInitializer);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetMent(const FText& InMent, const FText& InName);

public:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
