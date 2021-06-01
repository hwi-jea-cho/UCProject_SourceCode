#include "CLiteracyComponent.h"
#include "Global.h"
#include "Components/Actor/CTalkableComponent.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Character/CStateComponent.h"
#include "Components/PlayerOnly/CMenuComponent.h"
#include "TableDatas/NonPlayerMent.h"
#include "Characters/CPlayer.h"

UCLiteracyComponent::UCLiteracyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CHelpers::GetAsset<UDataTable>(&MentTable,
		"DataTable'/Game/_MyWorld/DataTables/FMentList.FMentList'");

}

void UCLiteracyComponent::BeginPlay()
{
	Super::BeginPlay();

	Interactor = CHelpers::GetComponent<UCInteractorComponent>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	Menu = CHelpers::GetComponent<UCMenuComponent>(GetOwner());
	
}


bool UCLiteracyComponent::BeginTalk(UCTalkableComponent* InOther)
{
	CheckFalseResult(State->IsCanTalk(), false);

	Contacted = InOther;

	State->SetTalkMode();
	Contacted->BeginTalk(this);

	Menu->OpenTalk();
	NextTalk();

	return true;
}

void UCLiteracyComponent::CancelTalk()
{
	Menu->CloseTalk();

	CheckNull(Contacted);

	UCTalkableComponent* ended = Contacted;
	Contacted = nullptr;

	State->SetIdleMode();
	ended->EndTalk();
}

void UCLiteracyComponent::NextTalk()
{
	if (Contacted == nullptr)
	{
		CancelTalk();
		return;
	}

	const FNonPlayerMent* mentDesc = nullptr;

	FName mentId = Contacted->GetCurrMentID();
	FString ContextString;
	MentTable->ForeachRow(ContextString, TFunctionRef<void(const FName&, const FNonPlayerMent&)>([&](const FName& InName, const FNonPlayerMent& InValue) {
		if (InName == mentId)
		{
			mentDesc = &InValue;
		}
	}));

	if (mentDesc == nullptr)
	{
		CancelTalk();
		return;
	}

	FText name = FText();
	if (mentDesc->SpeakerInteratorID.IsNone() == false)
	{
		name = Interactor->ConvertIdToName(mentDesc->SpeakerInteratorID);
	}
	FText ment = mentDesc->Ment;

	Contacted->TalkNext(mentDesc->NextMentID);
	Menu->SetTalkMent(name, ment);
}
