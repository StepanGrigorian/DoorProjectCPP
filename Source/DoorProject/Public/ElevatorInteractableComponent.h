#pragma once
#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/TimelineComponent.h"
#include "ElevatorInteractableComponent.generated.h"

class USceneComponent;
class UElevatorInteractableComponent;
class UStaticMeshComponent;
class UBoxComponent;

UENUM()
enum DoorState
{
	Closed = 0,
	Opened = 1

};

UCLASS()
class DOORPROJECT_API UElevatorInteractableComponent : public UInteractableComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<UStaticMeshComponent> RightDoor;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> RightDoorClosed;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> RightDoorOpened;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<UStaticMeshComponent> LeftDoor;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> LeftDoorClosed;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> LeftDoorOpened;
	UPROPERTY(BlueprintReadonly, EditAnywhere)
		TObjectPtr<UCurveFloat> Curve;
	UPROPERTY()
		TEnumAsByte<DoorState> State = DoorState::Closed;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Widgets")
		TObjectPtr<UProgressSlider> ProgressWidget = nullptr;

private:
	FTimeline ProgressTimeline;
	FTimeline DoorTimeline;
public:
	UElevatorInteractableComponent();
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void StartInteraction(UInteractorComponent* interactor) override;

	virtual void EndInteraction(UInteractorComponent* interactor) override;

	UFUNCTION()
		void FinishedProgress();

	UFUNCTION()
		void UpdateProgress(float value);

	UFUNCTION()
		void UpdateDoor(float value);

	UFUNCTION()
		void ToggleDoorState();
};
