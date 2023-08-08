#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/SoftObjectPtr.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interactable.h"
#include "Interactor.h"
#include "Kicker.h"
#include "InteractorComponent.h"
#include "KickerComponent.h"

#include "MyCharacter.generated.h"

class UInputAction;

UCLASS()
class DOORPROJECT_API AMyCharacter : public ACharacter//, public IInteractor, public IKicker
{
	GENERATED_BODY()

public:
	AMyCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		TObjectPtr<UInputMappingContext> InputMapping = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		TObjectPtr<UInputAction> MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		TObjectPtr<UInputAction> RotateCameraAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		TObjectPtr<UInputAction> ClickAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		TObjectPtr<UInputAction> InteractAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		TObjectPtr<class UCameraComponent> Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		TObjectPtr<class USpringArmComponent> CameraArm = nullptr;


	UPROPERTY(EditAnywhere, Category = "Components")
		TObjectPtr<UInteractorComponent> Interactor;
	UPROPERTY(EditAnywhere, Category = "Components")
		TObjectPtr<UKickerComponent> Kicker;
	UPROPERTY(EditAnywhere, Category = "Collision")
		TEnumAsByte<ECollisionChannel> ClickTraceChannel = ECC_GameTraceChannel1;
	UPROPERTY(EditAnywhere)
		float Force;
	UPROPERTY(EditAnywhere)
		float LineLength;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnInteractionStart();
	virtual void OnInteractionEnd();

	//UFUNCTION()
	//	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		FVector CalculateKickDirection();
	//UPROPERTY()
	//	FInteract InteractDelegate;
private:
	void Move(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	UFUNCTION()
		void OnKick();
	//virtual void CheckLineAndKick_Implementation(FVector LineStart, FVector LineDirection, FVector KickDirection) override;

};
