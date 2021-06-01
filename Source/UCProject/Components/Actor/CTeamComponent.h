#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTeamComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetOn);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCTeamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTeamComponent();

protected:
	virtual void BeginPlay() override;

public:
	void OnTarget();
	void OffTarget();

public:
	UPROPERTY(BlueprintAssignable)
		FTargetOn OnTargetOn;

	UPROPERTY(BlueprintAssignable)
		FTargetOn OffTargetOn;
};
