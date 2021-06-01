#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NonPlayerMent.generated.h"

USTRUCT(BlueprintType)
struct UCPROJECT_API FNonPlayerMent : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FName SpeakerInteratorID;

	UPROPERTY(EditAnywhere)
		FText Ment;

	UPROPERTY(EditAnywhere)
		FName NextMentID;

};
