#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CHittedCollector.generated.h"

UCLASS()
class UCPROJECT_API UCHittedCollector : public UObject
{
	GENERATED_BODY()
	
public:
	bool CollectHitted(AActor* InHitted);
	void ResetCollection();

private:
	TArray<class AActor*> HittedActors;

};
