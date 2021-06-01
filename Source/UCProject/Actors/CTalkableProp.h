#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTalkableProp.generated.h"

UCLASS()
class UCPROJECT_API ACTalkableProp : public AActor
{
	GENERATED_BODY()

protected: // Actor Component
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCInteractorComponent* Interactor;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCTalkableComponent* Talkable;
	
public:	
	ACTalkableProp();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Interaction(class UCInteractorComponent* InOther);

};
