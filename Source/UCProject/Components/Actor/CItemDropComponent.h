#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CItemDropComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCItemDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCItemDropComponent();

private:
	UPROPERTY(EditAnywhere)
		class UCDropRateData* Data;

public:
	UFUNCTION(BlueprintCallable)
		class ACDropItemActor* SpawnDropItem(FTransform InTransform);
	

protected:
	virtual void BeginPlay() override;


};
