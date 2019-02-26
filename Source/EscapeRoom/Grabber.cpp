// Copyright Steve Gehrig 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "EscapeRoom.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float MaxDistance = 75.0f;
	AActor* ActorHit = (GetObjectAtLineTrace(MaxDistance)).GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("object hit: %s"), *(ActorHit->GetName()));
	}
}

FHitResult UGrabber::GetObjectAtLineTrace(float reach)
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewRotation;
	FHitResult LineTraceHit;
	//OUT: references to player location FVector and rotation FRotator
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewRotation.Vector() * reach;

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return LineTraceHit;
}
