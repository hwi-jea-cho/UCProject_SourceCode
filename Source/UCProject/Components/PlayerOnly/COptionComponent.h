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
		float MouseLookRate = 1.0f;

	UPROPERTY(EditAnywhere)
		float HorizontalLookRate = 45.0f;

	UPROPERTY(EditAnywhere)
		float VerticalLookRate = 45.0f;

	UPROPERTY(EditAnywhere)
		float ZoomRate = 10.0f;


protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetMouseLookRate() const { return MouseLookRate; }
	FORCEINLINE float GetHorizontalLookRate() const { return HorizontalLookRate; }
	FORCEINLINE float GetVerticalLookRate() const { return VerticalLookRate; }
	FORCEINLINE float GetZoomRate() const { return ZoomRate; }
		
};
