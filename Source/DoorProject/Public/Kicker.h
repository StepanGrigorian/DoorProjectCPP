#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kicker.generated.h"

UINTERFACE(MinimalAPI)
class UKicker : public UInterface
{
	GENERATED_BODY()
};

class DOORPROJECT_API IKicker
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void CheckLineAndKick(FVector LineStart, FVector LineDirection, FVector KickDirection);
};
