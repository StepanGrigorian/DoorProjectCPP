#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KickerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOORPROJECT_API UKickerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UKickerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		virtual void CheckLineAndKick(FVector LineStart, FVector LineEnd, FVector KickDirection);

	UPROPERTY(EditAnywhere, Category = "Collision")
		TEnumAsByte<ECollisionChannel> ClickTraceChannel = ECC_GameTraceChannel1;
	UPROPERTY(EditAnywhere)
		float Force;
	UPROPERTY(EditAnywhere)
		float LineLength;
		
};
