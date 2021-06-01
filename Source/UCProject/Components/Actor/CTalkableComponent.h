#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTalkableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTalk, FName, InCurrMentID);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCTalkableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ment")
		FName FirstMentID = "None";

public:
	UCTalkableComponent();

protected:
	virtual void BeginPlay() override;

public:
	void BeginTalk(class UCLiteracyComponent* InOther);
	void TalkNext(FName InNextMentID);
	void EndTalk();

	void CancelTalk();
	void SetFirstMentID(FName InFirstMentID);
	FORCEINLINE FName GetCurrMentID() const { return CurrMentID; }

public:
	UPROPERTY(BlueprintAssignable)
		FTalk OnNext_Talk;

	UPROPERTY(BlueprintAssignable)
		FTalk OnEnd_Talk;

private:
	FName CurrMentID;
	class UCLiteracyComponent* Contacted;

};
