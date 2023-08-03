// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kicker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKicker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DOORPROJECT_API IKicker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
		void CheckLineAndKick(FVector LineStart, FVector LineDirection, FVector KickDirection);
};
