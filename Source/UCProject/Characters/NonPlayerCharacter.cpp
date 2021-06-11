#include "NonPlayerCharacter.h"
#include "Global.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Actor/CTalkableComponent.h"
#include "Components/Character/CStanceComponent.h"
#include "Components/PlayerOnly/CLiteracyComponent.h"
#include "Characters/CPlayer.h"

ANonPlayerCharacter::ANonPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &Interactor, "Interactor");
	CHelpers::CreateActorComponent(this, &Talkable, "Talkable");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Stance, "Stance");

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

void ANonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeHeadRotation();
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
		SetWatchingActor(player);
}

void ANonPlayerCharacter::OffInteractorConnected(UCInteractorComponent* InOther)
{
	ACPlayer* player = Cast<ACPlayer>(InOther->GetOwner());

	if (!!player)
		SetWatchingActor(nullptr);
}

void ANonPlayerCharacter::OnEnd_Talk(FName InCurrMentID)
{
	State->SetIdleMode();
}


void ANonPlayerCharacter::SetWatchingActor(AActor* InActor)
{
	WatchingActor = InActor;

	if (InActor == nullptr)
		Stance->SetHeadRotation(FRotator());
}

void ANonPlayerCharacter::ChangeHeadRotation()
{
	CheckNull(WatchingActor);

	FRotator src = GetOwner()->GetActorRotation();
	FRotator dest = UKismetMathLibrary::FindLookAtRotation(
		GetOwner()->GetActorLocation(), WatchingActor->GetActorLocation()
	);

	if (FVector::DotProduct(src.Vector(), dest.Vector()) >= 0.0f)
	{
		FRotator result = (dest - src);
		Stance->SetHeadRotation(result);
	}
	else
	{
		Stance->SetHeadRotation(FRotator());
	}

}
