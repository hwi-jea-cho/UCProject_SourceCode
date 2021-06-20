#include "CAttackment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Actor/CTeamComponent.h"
#include "Components/Character/CStateComponent.h"
#include "Components/Attachment/CComboComponent.h"
#include "CAttachment.h"

ACAttackment::ACAttackment()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACAttackment::SetData(FAttackmentData InData)
{
	Data = InData;
}

void ACAttackment::BeginPlay()
{
	OwnerWeapon = Cast<ACAttachment>(GetOwner());
	OwnerCharacter = Cast<ACharacter>(OwnerWeapon->GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Combo = CHelpers::GetComponent<UCComboComponent>(OwnerCharacter);
	AttackTarget = CHelpers::GetComponent<UCTeamComponent>(OwnerCharacter);

	// 블프
	Super::BeginPlay();
}

void ACAttackment::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	switch (EndPlayReason)
	{
	case EEndPlayReason::Type::Destroyed:
		ReverseSpawnNaxtCombos();
		break;
	}

}

// public
bool ACAttackment::IsVialdCommend(EAttackCommend InCommend)
{
	return Data.Commend == InCommend;
}

// public
ACAttackment* ACAttackment::GetNextCombo(EAttackCommend InCommend)
{
	for (ACAttackment* naxt : NextCombos)
	{
		if (naxt->IsVialdCommend(InCommend))
		{
			return naxt;
		}
	}

	return nullptr;
}

void ACAttackment::AddNaxtCombo(ACAttackment* InNext)
{
	NextCombos.Add(InNext);
}

void ACAttackment::ReverseSpawnNaxtCombos()
{
	for (ACAttackment* naxt : NextCombos)
	{
		naxt->ReverseSpawnNaxtCombos();
		naxt->Destroy();
	}
	NextCombos.Empty();
}

void ACAttackment::TakeDamage_Attackment(AActor* InAttackerCauser, AActor* InAttackTarget)
{
	UCTeamComponent* attackTargetTeam = CHelpers::GetComponent<UCTeamComponent>(InAttackTarget);

	CheckNull(attackTargetTeam);
	CheckFalse(attackTargetTeam->IsEnemy());

	//Take Damage
	FDamageEvent e;
	InAttackTarget->TakeDamage(1.0f, e, OwnerCharacter->GetController(), InAttackerCauser);
}


// ComboComponent
void ACAttackment::Attack_Implementation()
{
	if (Data.bCanMove == false)
	{
		State->SetStop();
	}

	if (!!Data.AnimMontage)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRatio, Data.StartSection);
	else
	{
		Attacked();
	}
}

// Notify (공격 종료)
void ACAttackment::Attacked_Implementation()
{
	if (Data.bCanMove == false)
	{
		State->SetMove();
	}

	if (OnAttacked.IsBound())
	{
		OnAttacked.Execute();
	}

}


