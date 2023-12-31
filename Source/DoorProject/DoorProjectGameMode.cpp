// Copyright Epic Games, Inc. All Rights Reserved.

#include "DoorProjectGameMode.h"
#include "DoorProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADoorProjectGameMode::ADoorProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
