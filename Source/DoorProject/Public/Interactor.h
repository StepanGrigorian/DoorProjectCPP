#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Interactor.generated.h"

UINTERFACE(MinimalAPI)
class UInteractor : public UInterface
{
	GENERATED_BODY()
};

class DOORPROJECT_API IInteractor
{
	GENERATED_BODY()

public:
	virtual void OnInteract() = 0;
};
