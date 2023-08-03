#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Kickable.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InteractableActor.generated.h"

UCLASS()
class DOORPROJECT_API AInteractableActor : public AActor, public IInteractable, public IKickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor(); UPROPERTY(EditAnywhere)
		TObjectPtr<UBoxComponent> Collision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TObjectPtr<UStaticMeshComponent> Mesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void Interaction() override;
	virtual void Kick_Implementation(FVector impulse) override;
};
