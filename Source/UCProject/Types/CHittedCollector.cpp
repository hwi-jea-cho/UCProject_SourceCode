#include "CHittedCollector.h"

bool UCHittedCollector::CollectHitted(AActor* InHitted)
{
	for (const AActor* other : HittedActors)
	{
		if (other == InHitted->GetOwner())
			return false;
	}
	HittedActors.Add(InHitted->GetOwner());

	return true;
}

void UCHittedCollector::ResetCollection()
{
	HittedActors.Empty();
}
