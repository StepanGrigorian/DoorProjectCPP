#include "InteractableComponent.h"
#include "InteractorComponent.h"
#include <Kismet/KismetSystemLibrary.h>

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Collision)
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
		other->InteractDelegate.AddDynamic(this, &UInteractableComponent::Interaction);
	}
}

void UInteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UInteractorComponent* other = OtherActor->GetComponentByClass<UInteractorComponent>();
	if (IsValid(other) && other->InteractDelegate.IsBound())
	{
		other->InteractDelegate.RemoveDynamic(this, &UInteractableComponent::Interaction);
	}
}

void UInteractableComponent::Interaction()
{
	UKismetSystemLibrary::PrintString(this, "Interact with interactable actor component");
}
