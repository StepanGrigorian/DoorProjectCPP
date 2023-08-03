// Fill out your copyright notice in the Description page of Project Settings.


#include "KickableComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UKickableComponent::UKickableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UKickableComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UKickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UKickableComponent::Kick(FVector Impulse)
{
	if (IsValid(Mesh))
	{
		Mesh->AddImpulse(Impulse);
		UKismetSystemLibrary::PrintString(GetOwner(), "Kickable comp");
	}
}