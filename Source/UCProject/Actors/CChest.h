#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CChest.generated.h"

UCLASS()
class UCPROJECT_API ACChest : public AActor
{
	GENERATED_BODY()


protected: // Scene Component
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		USceneComponent* SceneRoot;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		USceneComponent* SpawnTransform;

protected: // Actor Component
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCInteractorComponent* Interactor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCItemDropComponent* ItemDroppable;

protected:
	// 열리는 시간
	UPROPERTY(BlueprintReadWrite)
		float OpenTime = 3.0f;

	UPROPERTY(BlueprintReadWrite)
		float TimeCycle = 0.03f;


public:
	ACChest();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnInteraction(class UCInteractorComponent* InOther);

	UFUNCTION()
		void UpdateOpenning();

public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateOpening(float InRunTime);

private:
	float RunTime = 0.0f;
	FTimerHandle OpenningTimer;
	FTimerDynamicDelegate Openning;

};
