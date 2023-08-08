#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class UInteractorComponent;
class UPrimitiveComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class DOORPROJECT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<UBoxComponent> Collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<UStaticMeshComponent> Mesh;

protected:
	virtual void BeginPlay() override;
	TObjectPtr<UInteractorComponent> Interactor = nullptr;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		virtual void StartInteraction(UInteractorComponent* interactor);
	UFUNCTION()
		virtual void EndInteraction(UInteractorComponent* interactor);
	UFUNCTION()
		virtual void Initialize();

};
