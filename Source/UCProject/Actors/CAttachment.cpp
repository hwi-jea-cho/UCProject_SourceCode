#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Character/CStanceComponent.h"
#include "Components/Attachment/CComboComponent.h"

ACAttachment::ACAttachment()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateActorComponent<UCComboComponent>(this, &Combo, "Combo");
}

void ACAttachment::SetData(const FAttachmentData& InData)
{
	Data = InData;
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Stance = CHelpers::GetComponent<UCStanceComponent>(OwnerCharacter);

	// 블프
	Super::BeginPlay();
}

void ACAttachment::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);

}


// Action Component
void ACAttachment::Equip_Implementation()
{
	const FMontageDesc& montageDesc = Data.EquipmentMontage;
	if (!!montageDesc.AnimMontage)
		OwnerCharacter->PlayAnimMontage(montageDesc.AnimMontage, montageDesc.PlayRatio, montageDesc.StartSection);
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

// Notify (어타치먼트)
void ACAttachment::Begin_Equip_Implementation()
{
	bEquip = true;
}

// Notify (동작 완료)
void ACAttachment::End_Equip_Implementation()
{
	if (bEquip == true)
	{
		OnEquip();
		Stance->SetOneHandMode();
	}
}


// Action Component
void ACAttachment::Unequip_Implementation()
{
	const FMontageDesc& montageDesc = Data.UnequipmentMontage;
	if (!!montageDesc.AnimMontage)
		OwnerCharacter->PlayAnimMontage(montageDesc.AnimMontage, montageDesc.PlayRatio, montageDesc.StartSection);
	else
	{
		Begin_Unequip();
		End_Unequip();
	}
}

// Notify (어타치먼트)
void ACAttachment::Begin_Unequip_Implementation()
{
	bEquip = false;
}

// Notify (동작 완료)
void ACAttachment::End_Unequip_Implementation()
{
	if (bEquip == false)
	{
		OnUnequip();
		Stance->SetUnarmedMode();
	}
}
