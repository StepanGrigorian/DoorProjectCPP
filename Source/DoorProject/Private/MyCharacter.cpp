#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/RotationMatrix.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kickable.h"
#include "CollisionQueryParams.h"

AMyCharacter::AMyCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Interactor = CreateDefaultSubobject<UInteractorComponent>("Interactor");
	Kicker = CreateDefaultSubobject<UKickerComponent>("Kicker");

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
	Input->BindAction(RotateCameraAction, ETriggerEvent::Triggered, this, &AMyCharacter::RotateCamera);
	Input->BindAction(ClickAction, ETriggerEvent::Started, this, &AMyCharacter::OnKick);
	Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::OnInteract);

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnBeginOverlap);
	//GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnEndOverlap);
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Input.X);
	AddMovementInput(Right, Input.Y);
}

void AMyCharacter::RotateCamera(const FInputActionValue& Value)
{
	auto input = Value.Get<FVector>();

	AddControllerYawInput(input.X);
	AddControllerPitchInput(input.Y);
}

void AMyCharacter::OnKick()
{
	Kicker->CheckLineAndKick(Camera->GetComponentLocation(), Camera->GetForwardVector(), CalculateKickDirection());
	IKicker::Execute_CheckLineAndKick(this, Camera->GetComponentLocation(), Camera->GetForwardVector(), CalculateKickDirection());
}

//void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	//UKismetSystemLibrary::PrintString(this, "CharacterStartOverlap");
//}
//
//
//void AMyCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	//UKismetSystemLibrary::PrintString(this, "CharacterEndOverlap");
//}

void AMyCharacter::OnInteract()
{
	InteractDelegate.Broadcast();
	Interactor->InteractDelegate.Broadcast();
}

FVector AMyCharacter::CalculateKickDirection()
{
	const FRotator YawRotation(0, Controller->GetControlRotation().Yaw - 45, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) + FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	return Direction;
}
void AMyCharacter::CheckLineAndKick_Implementation(FVector LineStart, FVector LineDirection, FVector KickDirection)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	FHitResult Result;
	if (GetWorld()->LineTraceSingleByChannel(
		Result,
		LineStart,
		LineStart + LineDirection * LineLength,
		ClickTraceChannel,
		CollisionParams))
	{
		AActor* other = Result.GetActor();
		if (other->Implements<UKickable>())
		{
			IKickable::Execute_Kick(other, KickDirection * Force);
		}
	}
}