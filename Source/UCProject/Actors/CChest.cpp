#include "CChest.h"
#include "Global.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Actor/CItemDropComponent.h"

ACChest::ACChest()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateComponent<USceneComponent>(this, &SceneRoot, "SceneRoot");
	CHelpers::CreateComponent<USceneComponent>(this, &SpawnTransform, "SpawnTransform", SceneRoot);
	CHelpers::CreateActorComponent<UCInteractorComponent>(this, &Interactor, "Interactor");
	CHelpers::CreateActorComponent<UCItemDropComponent>(this, &ItemDroppable, "ItemDroppable");

	Interactor->SetInteractorType(EInteractorType::Chest);
	Interactor->SetInteractorID("Chest");
}

void ACChest::BeginPlay()
{
	Super::BeginPlay();
	
	Interactor->OnInteraction.AddDynamic(this, &ACChest::OnInteraction);
	Openning.BindUFunction(this, "UpdateOpenning");
}

void ACChest::OnInteraction(UCInteractorComponent* InOther)
{
	Interactor->DisableInteraction();

	FTransform tranform;
	tranform = SpawnTransform->GetComponentTransform();
	tranform.SetScale3D(FVector::OneVector);
	ItemDroppable->SpawnDropItem(tranform);

	OpenningTimer = UKismetSystemLibrary::K2_SetTimerDelegate(Openning, TimeCycle, true);
}

void ACChest::UpdateOpenning()
{
	RunTime += TimeCycle;

	UpdateOpening(RunTime);

	if (RunTime >= OpenTime)
	{
		UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), OpenningTimer);
		Destroy();
	}
}

