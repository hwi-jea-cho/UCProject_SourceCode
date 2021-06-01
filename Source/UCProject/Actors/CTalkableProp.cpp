#include "CTalkableProp.h"
#include "Global.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Actor/CTalkableComponent.h"
#include "Components/PlayerOnly/CLiteracyComponent.h"

ACTalkableProp::ACTalkableProp()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateActorComponent(this, &Interactor, "Interactor");
	CHelpers::CreateActorComponent(this, &Talkable, "Talkable");

	Interactor->SetInteractorType(EInteractorType::NPC);
}

void ACTalkableProp::BeginPlay()
{
	Super::BeginPlay();

	Interactor->OnInteraction.AddDynamic(this, &ACTalkableProp::Interaction);
}

void ACTalkableProp::Interaction(UCInteractorComponent* InOther)
{
	UCLiteracyComponent* literacy =
		CHelpers::GetComponent<UCLiteracyComponent>(InOther->GetOwner());

	CheckNull(literacy);

	literacy->BeginTalk(Talkable);
}

