#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDropItemActor.generated.h"

UCLASS()
class UCPROJECT_API ACDropItemActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DropItem")
		FName ItemID = "None";

	UPROPERTY(EditAnywhere, Category = "DropItem")
		int32 ItemCount = 1;

protected: // Actor Component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCInteractorComponent* Interactor;

public:	
	ACDropItemActor();
	void SetData(FName InItemID, int32 InItemCount);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Interaction(class UCInteractorComponent* InOther);

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE FName GetItemID() const { return ItemID; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetItemCount() const { return ItemCount; }

};
