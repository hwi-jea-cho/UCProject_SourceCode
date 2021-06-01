#include "CConsumableActor.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Types/CInventoryItem_Consumable.h"

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
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}


void ACConsumableActor::StartConsum()
{
	CheckFalse(State->IsCanConsum());

	State->SetConsumMode();
	State->SetStop();
	State->OnStateTypeChanged.AddDynamic(this, &ACConsumableActor::OnStateTypeChanged);

	if (Begin_Consum.IsBound())
		Begin_Consum.Broadcast();

	const FMontageDesc& montageDesc = Desc->ConsumMontage;
	if (!!montageDesc.AnimMontage)
	{
		OwnerCharacter->PlayAnimMontage(montageDesc.AnimMontage, montageDesc.PlayRatio, montageDesc.StartSction);
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

void ACConsumableActor::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	CheckTrue(InPrevType != EStateType::Consum);

	FinishConsum();
}

void ACConsumableActor::FinishConsum()
{
	State->OnStateTypeChanged.RemoveDynamic(this, &ACConsumableActor::OnStateTypeChanged);

	if (State->IsConsumMode())
	{
		State->SetMove();
		State->SetIdleMode();
	}

	if (End_Consum.IsBound())
		End_Consum.Broadcast();
}

