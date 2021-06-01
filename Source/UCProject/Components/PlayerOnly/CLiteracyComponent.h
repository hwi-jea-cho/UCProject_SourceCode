#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CLiteracyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCLiteracyComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ment")
		class UDataTable* MentTable;

public:
	UCLiteracyComponent();

protected:
	virtual void BeginPlay() override;

public:
	bool BeginTalk(class UCTalkableComponent* InOther);
	void CancelTalk();
	void NextTalk();

private:
	class UCInteractorComponent* Interactor;
	class UCStateComponent* State;
	class UCMenuComponent* Menu;


	class UCTalkableComponent* Contacted;
};
