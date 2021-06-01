#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/CStatusInstance.h"
#include "CUserWidget_Menu.generated.h"

UENUM(BlueprintType)
enum class EMenuType : uint8
{
	None, Equipment, Consumable,
};

UCLASS()
class UCPROJECT_API UCUserWidget_Menu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
		class UCUserWidget_Equipment* MenuEquipment;

	UPROPERTY(meta = (BindWidget))
		class UCUserWidget_Consumable* MenuConsumable;

public:
	UCUserWidget_Menu(const FObjectInitializer& InObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
		void OpenStackable();

	UFUNCTION(BlueprintCallable)
		void OpenEquipment();

	UFUNCTION(BlueprintCallable)
		void OpenNone();

	void Open();
	void Closs();

	UFUNCTION(BlueprintPure)
		FStatusData GetCharacterStatus() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void OnOpened();

	FORCEINLINE bool IsOpened() const { return bOpenedMenu; }

private:
	void SetMenu(EMenuType InNextMenu);

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	bool bOpenedMenu = false;
	EMenuType currMenu = EMenuType::None;
	class UCInventoryComponent* Inventory;

};
