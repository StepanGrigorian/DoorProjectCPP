// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "InteractorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteract, UInteractorComponent*, Interactor);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DOORPROJECT_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractorComponent();
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		FInteract InteractionStartDelegate;
	UPROPERTY()
		FInteract InteractionEndDelegate;

};
