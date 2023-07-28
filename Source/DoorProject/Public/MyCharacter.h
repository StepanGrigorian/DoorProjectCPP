#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/SoftObjectPtr.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "MyCharacter.generated.h"
class UInputAction;

UCLASS()
class DOORPROJECT_API AMyCharacter : public ACharacter
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		TObjectPtr<class UCameraComponent> Camera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		TObjectPtr<class USpringArmComponent> CameraArm = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void RotateCamera(const FInputActionValue& Value);
};
