#include "InteractableActor.h"
#include "Interactor.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Mesh);
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnEndOverlap);
	}
}

void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UKismetSystemLibrary::PrintString(this, "Actor OnBeginOverlap");
	if (OtherActor->Implements<UInteractor>())
	{
		AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
		if (Character)
		{
			//Character->InteractDelegate.AddDynamic(this, &AInteractableActor::Interaction);
		}
	}
}

void AInteractableActor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UKismetSystemLibrary::PrintString(this, "Actor OnEndOverlap");
	if (OtherActor->Implements<UInteractor>())
	{
		AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
		if (IsValid(Character))
		{
			//Character->InteractDelegate.RemoveDynamic(this, &AInteractableActor::Interaction);
		}
	}
}

void AInteractableActor::Interaction()
{
	UKismetSystemLibrary::PrintString(this, "Interact with interactable actor");
}

void AInteractableActor::Kick_Implementation(FVector impulse)
{
	if (IsValid(Mesh))
	{
		Mesh->AddImpulse(impulse);
	}
}