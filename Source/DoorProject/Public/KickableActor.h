// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectPtr.h"
#include "Kickable.h"
#include "Components/StaticMeshComponent.h"
#include "KickableActor.generated.h"

UCLASS()
class DOORPROJECT_API AKickableActor : public AActor, public IKickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKickableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
