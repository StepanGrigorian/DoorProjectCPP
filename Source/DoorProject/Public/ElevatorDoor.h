#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "ElevatorDoor.generated.h"

class USceneComponent;
class UElevatorInteractableComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UWidgetComponent;
class UUserWidget;
class UProgressSlider;

UCLASS()
class DOORPROJECT_API AElevatorDoor : public ADoor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		TObjectPtr<UElevatorInteractableComponent> ElevatorComponent;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<USceneComponent> Root;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<USceneComponent> DoorPositionsRoot;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<UStaticMeshComponent> RightDoor;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<UStaticMeshComponent> LeftDoor;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Meshes")
		TObjectPtr<UBoxComponent> Collision;

	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> RightDoorClosed;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> RightDoorOpened;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> LeftDoorClosed;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "DoorPositions")
		TObjectPtr<USceneComponent> LeftDoorOpened;
	UPROPERTY(BlueprintReadonly, EditAnywhere)
		TObjectPtr<UCurveFloat> Curve;
	UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Widgets")
		TObjectPtr<UWidgetComponent> ProgressWidgetComponent = nullptr;

public:
	AElevatorDoor();
	virtual void BeginPlay() override;
};
