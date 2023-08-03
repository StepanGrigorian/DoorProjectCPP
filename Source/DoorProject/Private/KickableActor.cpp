#include "KickableActor.h"
#include "Components/StaticMeshComponent.h"

AKickableActor::AKickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKickableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
