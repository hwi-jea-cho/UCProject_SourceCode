#include "NonPlayerCharacter.h"
#include "Global.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Actor/CTalkableComponent.h"
#include "Components/Character/CNpcPoseComponent.h"
#include "Components/PlayerOnly/CLiteracyComponent.h"
#include "Characters/CPlayer.h"

ANonPlayerCharacter::ANonPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateActorComponent(this, &Pose, "Pose");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Interactor, "Interactor");
	CHelpers::CreateActorComponent(this, &Talkable, "Talkable");

	Interactor->SetInteractorType(EInteractorType::NPC);
}

void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Interactor->OnInteraction.AddDynamic(this, &ANonPlayerCharacter::Interaction);
	Interactor->OnInteractorConnected.AddDynamic(this, &ANonPlayerCharacter::OnInteractorConnected);
	Interactor->OffInteractorConnected.AddDynamic(this, &ANonPlayerCharacter::OffInteractorConnected);
	Talkable->OnEnd_Talk.AddDynamic(this, &ANonPlayerCharacter::OnEnd_Talk);

}

void ANonPlayerCharacter::Interaction(UCInteractorComponent* InOther)
{
	UCLiteracyComponent* literacy =
		CHelpers::GetComponent<UCLiteracyComponent>(InOther->GetOwner());

	CheckFalse(State->IsCanTalk());
	CheckFalse(literacy->BeginTalk(Talkable));

	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(
		GetActorLocation(), InOther->GetOwner()->GetActorLocation()
	);

	FRotator rotator = GetActorRotation();
	newRotator.Pitch = rotator.Pitch;
	newRotator.Roll = rotator.Roll;
	SetActorRotation(newRotator);

	State->SetTalkMode();

}

void ANonPlayerCharacter::OnInteractorConnected(UCInteractorComponent* InOther)
{
	ACPlayer* player = Cast<ACPlayer>(InOther->GetOwner());

	if (!!player)
		Pose->SetLookingAtActor(player);
}

void ANonPlayerCharacter::OffInteractorConnected(UCInteractorComponent* InOther)
{
	ACPlayer* player = Cast<ACPlayer>(InOther->GetOwner());

	if (!!player)
		Pose->SetLookingAtActor(nullptr);
}

void ANonPlayerCharacter::OnEnd_Talk(FName InCurrMentID)
{
	State->SetIdleMode();
}
