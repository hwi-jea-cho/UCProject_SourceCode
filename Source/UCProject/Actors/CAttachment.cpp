#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Types/CHittedCollector.h"
#include "Components/ShapeComponent.h"
#include "Components/Actor/CTeamComponent.h"
#include "Components/Character/CStanceComponent.h"
#include "Components/Attachment/CComboComponent.h"
#include "Actors/CAttackment.h"

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
	HittedCollector = NewObject<UCHittedCollector>();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Stance = CHelpers::GetComponent<UCStanceComponent>(OwnerCharacter);

	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* component : ShapeComponents)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
	}
	OffCollision();

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

void ACAttachment::AttachToCollision(USceneComponent* InComponent, FName InSocketName)
{
	InComponent->AttachToComponent
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


void ACAttachment::OnCollision()
{
	HittedCollector->ResetCollection();

	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACAttachment::OffCollision()
{
	HittedCollector->ResetCollection();

	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckFalse(HittedCollector->CollectHitted(OtherActor));

	CheckNull(Combo->GetCurrentAttack());
	Combo->GetCurrentAttack()->TakeDamage_Attackment(this, OtherActor);

}
