// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kickable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKickable : public UInterface
{
	GENERATED_BODY()
};

class DOORPROJECT_API IKickable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Interact")
		void Kick(FVector impulse);
};