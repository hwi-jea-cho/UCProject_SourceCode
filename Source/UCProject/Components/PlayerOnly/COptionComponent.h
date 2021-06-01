#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPROJECT_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCOptionComponent();

private:
	UPROPERTY(EditAnywhere)
		float HorizontalLookRate = 45.0f;

	UPROPERTY(EditAnywhere)
		float VerticalLookRate = 45.0f;

public:
	FORCEINLINE float GetHorizontalLookRate() const { return HorizontalLookRate; }
	FORCEINLINE float GetVerticalLookRate() const { return VerticalLookRate; }

protected:
	virtual void BeginPlay() override;

		
};
