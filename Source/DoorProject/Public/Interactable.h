#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class DOORPROJECT_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void Interaction() = 0;
};
