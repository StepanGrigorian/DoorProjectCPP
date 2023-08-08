#include "ElevatorDoor.h"
#include "ElevatorInteractableComponent.h"
#include "Components/MeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/ProgressSlider.h"
#include "Kismet/KismetSystemLibrary.h"

AElevatorDoor::AElevatorDoor()
{
	ElevatorComponent = CreateDefaultSubobject<UElevatorInteractableComponent>("ElevatorComponent");
	ElevatorComponent->bEditableWhenInherited = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	DoorPositionsRoot = CreateDefaultSubobject<USceneComponent>("DoorPositionsRoot");
	DoorPositionsRoot->SetupAttachment(Root);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>("RightDoor");
	RightDoor->SetupAttachment(Root);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>("LeftDoor");
	LeftDoor->SetupAttachment(Root);

	RightDoorClosed = CreateDefaultSubobject<USceneComponent>("RightDoorClosed");
	RightDoorClosed->SetupAttachment(DoorPositionsRoot);

	RightDoorOpened = CreateDefaultSubobject<USceneComponent>("RightDoorOpened");
	RightDoorOpened->SetupAttachment(DoorPositionsRoot);

	LeftDoorClosed = CreateDefaultSubobject<USceneComponent>("LeftDoorClosed");
	LeftDoorClosed->SetupAttachment(DoorPositionsRoot);

	LeftDoorOpened = CreateDefaultSubobject<USceneComponent>("LeftDoorOpened");
	LeftDoorOpened->SetupAttachment(DoorPositionsRoot);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Root);

	ProgressWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	ProgressWidgetComponent->SetupAttachment(Root);
}

void AElevatorDoor::BeginPlay()
{
	Super::BeginPlay();
}