#include "InteractableComponent.h"
#include "InteractorComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/KismetSystemLibrary.h>

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	Initialize();

}
void UInteractableComponent::Initialize()
{

	if (IsValid(Collision))
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &UInteractableComponent::OnBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &UInteractableComponent::OnEndOverlap);
	}
}
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractableComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UInteractorComponent* other = OtherActor->GetComponentByClass<UInteractorComponent>();
	if (IsValid(other))
	{
		other->InteractionStartDelegate.AddDynamic(this, &UInteractableComponent::StartInteraction);
		other->InteractionEndDelegate.AddDynamic(this, &UInteractableComponent::EndInteraction);
	}
}

void UInteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UInteractorComponent* other = OtherActor->GetComponentByClass<UInteractorComponent>();
	if (IsValid(other))
	{
		if (other->InteractionStartDelegate.IsBound()) other->InteractionStartDelegate.RemoveDynamic(this, &UInteractableComponent::StartInteraction);
		if (other->InteractionEndDelegate.IsBound()) other->InteractionEndDelegate.RemoveDynamic(this, &UInteractableComponent::EndInteraction);
	}
}

void UInteractableComponent::StartInteraction(UInteractorComponent* interactor)
{
	if (this->Interactor == nullptr)
	{
		UKismetSystemLibrary::PrintString(this, "Start interaction with interactable actor component");
		this->Interactor = interactor;
	}
}

void UInteractableComponent::EndInteraction(UInteractorComponent* interactor)
{
	if (this->Interactor == interactor)
	{
		UKismetSystemLibrary::PrintString(this, "End interaction with interactable actor component");
		this->Interactor = nullptr;
	}
}
