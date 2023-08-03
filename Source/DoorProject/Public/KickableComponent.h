#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/MeshComponent.h"
#include "KickableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOORPROJECT_API UKickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UKickableComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<UPrimitiveComponent> Mesh;
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Kick(FVector Impulse);
		
};
