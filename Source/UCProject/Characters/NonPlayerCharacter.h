#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/Character/CStateComponent.h"
#include "NonPlayerCharacter.generated.h"

UCLASS()
class UCPROJECT_API ANonPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected: // Actor Component
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCInteractorComponent* Interactor;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCNpcPoseComponent* Pose;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTalkableComponent* Talkable;


public:
	ANonPlayerCharacter();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Interaction(class UCInteractorComponent* InOther);

	UFUNCTION()
		void OnInteractorConnected(class UCInteractorComponent* InOther);

	UFUNCTION()
		void OffInteractorConnected(class UCInteractorComponent* InOther);

	UFUNCTION()
		void OnEnd_Talk(FName InCurrMentID);

};
