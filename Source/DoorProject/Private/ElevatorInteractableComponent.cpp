#include "ElevatorInteractableComponent.h"
#include "InteractorComponent.h"
#include "ElevatorDoor.h"
#include "Components/MeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/ProgressSlider.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Image.h"
UElevatorInteractableComponent::UElevatorInteractableComponent()
{

}

void UElevatorInteractableComponent::BeginPlay()
{
	AActor* Parent = GetOwner();
	if (IsValid(Parent))
	{
		AElevatorDoor* Door = Cast<AElevatorDoor>(Parent);
		Collision = Door->Collision;
		RightDoor = Door->RightDoor;
		RightDoorClosed = Door->RightDoorClosed;
		RightDoorOpened = Door->RightDoorOpened;
		LeftDoor = Door->LeftDoor;
		LeftDoorClosed = Door->LeftDoorClosed;
		LeftDoorOpened = Door->LeftDoorOpened;
		Door->ProgressWidgetComponent->InitWidget();
		ProgressWidget = Cast<UProgressSlider>(Door->ProgressWidgetComponent->GetUserWidgetObject());
		UKismetSystemLibrary::PrintString(this, "const");
	}
	Super::BeginPlay();
	FOnTimelineFloat ProgressFloat;
	FOnTimelineEvent FinishedProgressEvent;
	ProgressFloat.BindUFunction(this, FName("UpdateProgress"));
	FinishedProgressEvent.BindUFunction(this, FName("FinishedProgress"));
	if (IsValid(Curve))
	{
		ProgressTimeline.AddInterpFloat(Curve, ProgressFloat);
	}
	ProgressTimeline.SetTimelineFinishedFunc(FinishedProgressEvent);

	FOnTimelineFloat DoorFloat;
	DoorFloat.BindUFunction(this, FName("UpdateDoor"));
	if (IsValid(Curve))
	{
		DoorTimeline.AddInterpFloat(Curve, DoorFloat);
	}
	if (IsValid(ProgressWidget) && IsValid(ProgressWidget->SliderImage))
	{
		ProgressWidget->SliderImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UElevatorInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	ProgressTimeline.TickTimeline(DeltaTime);
	DoorTimeline.TickTimeline(DeltaTime);
	if(IsValid(Interactor))
	UKismetSystemLibrary::PrintString(this, "Interactor");
}

void UElevatorInteractableComponent::StartInteraction(UInteractorComponent* interactor)
{
	if (this->Interactor == nullptr)
	{
		ProgressTimeline.Play();
		UKismetSystemLibrary::PrintString(this, "Start interaction actor component override");
		this->Interactor = interactor;
	}
}

void UElevatorInteractableComponent::EndInteraction(UInteractorComponent* interactor)
{
	if (this->Interactor == interactor)
	{
		UKismetSystemLibrary::PrintString(this, "End interaction actor component override");
		ProgressTimeline.Reverse();
		this->Interactor = nullptr;
	}
}

void UElevatorInteractableComponent::FinishedProgress()
{
	if (ProgressTimeline.GetPlaybackPosition() == ProgressTimeline.GetTimelineLength())
	{
		UKismetSystemLibrary::PrintString(this, "Finished");
		ToggleDoorState();
		ProgressTimeline.SetNewTime(0);
	}
	if (IsValid(ProgressWidget) && IsValid(ProgressWidget->SliderImage))
	{
		ProgressWidget->SliderImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UElevatorInteractableComponent::UpdateProgress(float Value)
{
	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(Value));
	if (IsValid(ProgressWidget) && IsValid(ProgressWidget->SliderImage))
	{
		if (Value > 0)
		{
			ProgressWidget->SliderImage->SetVisibility(ESlateVisibility::Visible);
		}
		ProgressWidget->SliderImage->GetDynamicMaterial()->SetScalarParameterValue("Value", Value);
	}
}

void UElevatorInteractableComponent::UpdateDoor(float value)
{
	if (IsValid(LeftDoor) && IsValid(LeftDoorClosed) && IsValid(LeftDoorOpened))
	{
		LeftDoor->SetWorldLocation(FMath::Lerp(LeftDoorClosed->GetComponentLocation(), LeftDoorOpened->GetComponentLocation(), value));
	}
	if (IsValid(RightDoor) && IsValid(RightDoorClosed) && IsValid(RightDoorOpened))
	{
		RightDoor->SetWorldLocation(FMath::Lerp(RightDoorClosed->GetComponentLocation(), RightDoorOpened->GetComponentLocation(), value));
	}
}

void UElevatorInteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UInteractorComponent* other = OtherActor->GetComponentByClass<UInteractorComponent>();
	if (IsValid(other))
	{
		if (other->InteractionStartDelegate.IsBound()) other->InteractionStartDelegate.RemoveDynamic(this, &UInteractableComponent::StartInteraction);
		if (other->InteractionEndDelegate.IsBound()) other->InteractionEndDelegate.RemoveDynamic(this, &UInteractableComponent::EndInteraction);
		EndInteraction(other);
	}
}
void UElevatorInteractableComponent::ToggleDoorState()
{
	if (State == DoorState::Closed)
	{
		DoorTimeline.Play();
		State = DoorState::Opened;
	}
	else if (State == DoorState::Opened)
	{
		DoorTimeline.Reverse();
		State = DoorState::Closed;
	}
}