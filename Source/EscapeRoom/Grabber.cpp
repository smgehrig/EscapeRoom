// Copyright Steve Gehrig 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "EscapeRoom.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	bWantsBeginPlay = true;

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	Super::BeginPlay();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("object dragging"));
		PhysicsHandle->SetTargetLocation(GetLineEndTrace());
	}
}

FVector UGrabber::GetLineEndTrace()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewRotation;
	FHitResult LineTraceHit;
	//OUT: references to player location FVector and rotation FRotator
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewRotation
	);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewRotation.Vector() * 75.0f;
	return LineTraceEnd;
}

void UGrabber::Grab()
{
	float MaxDistance = 75.0f;
	auto HitResult = GetObjectAtLineTrace(MaxDistance);
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) 
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetObjectAtLineTrace(float reach)
{
	FVector LineTraceEnd = GetLineEndTrace();
	FVector PlayerViewPointLocation;
	FRotator PlayerViewRotation;
	FHitResult LineTraceHit;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewRotation
	);
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);
	return LineTraceHit;
}
