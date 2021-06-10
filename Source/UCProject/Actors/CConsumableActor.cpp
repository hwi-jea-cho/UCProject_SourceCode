#include "CConsumableActor.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Types/CInventoryItem_Consumable.h"
#include "Components/Character/CStateComponent.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"

ACConsumableActor::ACConsumableActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACConsumableActor::SetData(UCInventoryItem_Consumable* InItem, const FConsumableDesc* InDesc)
{
	Item = InItem;
	Desc = InDesc;
}

void ACConsumableActor::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerState = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	OwnerComponent = CHelpers::GetComponent<UCQuickConsumableComponent>(GetOwner());
}


void ACConsumableActor::StartConsum()
{
	CheckFalse(OwnerState->IsCanConsum());
	CheckTrue(OwnerComponent->GetCurrActor() != nullptr);

	OwnerComponent->SetCurrActor(this);
	OwnerState->SetConsumMode();
	OwnerState->SetStop();

	if (Begin_Consum.IsBound())
		Begin_Consum.Broadcast();

	const FMontageDesc& montageDesc = Desc->ConsumMontage;
	if (!!montageDesc.AnimMontage)
	{
		OwnerCharacter->PlayAnimMontage(montageDesc.AnimMontage, montageDesc.PlayRatio, montageDesc.StartSection);
	}
	else
	{
		Consum();
		FinishConsum();
	}
}

void ACConsumableActor::Consum()
{
	Item->Consum();

	if (OnConsum.IsBound())
		OnConsum.Broadcast();
}

void ACConsumableActor::FinishConsum()
{
	if (OwnerState->IsConsumMode())
	{
		OwnerState->SetMove();
		OwnerState->SetIdleMode();
	}

	if (End_Consum.IsBound())
		End_Consum.Broadcast();

	OwnerComponent->SetCurrActorNull();
}

