#include "KickerComponent.h"
#include "KickableComponent.h"

UKickerComponent::UKickerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UKickerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UKickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UKickerComponent::CheckLineAndKick(FVector LineStart, FVector LineDirection, FVector KickDirection)
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
		UKickableComponent* other = Result.GetActor()->GetComponentByClass<UKickableComponent>();
		if (IsValid(other))
		{
			other->Kick(KickDirection * Force);
		}
	}
}
