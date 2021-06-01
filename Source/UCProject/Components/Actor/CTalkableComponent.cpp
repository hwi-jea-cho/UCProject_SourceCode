#include "CTalkableComponent.h"
#include "Global.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/PlayerOnly/CLiteracyComponent.h"

UCTalkableComponent::UCTalkableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UCTalkableComponent::BeginPlay()
{
	Super::BeginPlay();

	UCInteractorComponent* ownerInteractor 
		= CHelpers::GetComponent<UCInteractorComponent>(GetOwner());

	if (FirstMentID.IsNone())
	{
		FirstMentID = ownerInteractor->GetInteractorID();
	}

	CurrMentID = FirstMentID;
}

void UCTalkableComponent::BeginTalk(UCLiteracyComponent* InOther)
{
	Contacted = InOther;
}

void UCTalkableComponent::TalkNext(FName InNextMentID)
{
	if (OnNext_Talk.IsBound())
		OnNext_Talk.Broadcast(CurrMentID);

	CurrMentID = InNextMentID;
}

void UCTalkableComponent::EndTalk()
{
	if (OnEnd_Talk.IsBound())
		OnEnd_Talk.Broadcast(CurrMentID);

	CurrMentID = FirstMentID;
	Contacted = nullptr;
}

void UCTalkableComponent::CancelTalk()
{
	CheckNull(Contacted);

	Contacted->CancelTalk();
}

void UCTalkableComponent::SetFirstMentID(FName InFirstMentID)
{
	FirstMentID = InFirstMentID;
}

