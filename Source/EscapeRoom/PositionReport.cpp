// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "EscapeRoom.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetName();
	FVector ObjectLocation = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Position reporting: %s"), *ObjectName);
	UE_LOG(LogTemp, Warning, TEXT("Position reporting: %f, %f, %f"), ObjectLocation.X, ObjectLocation.Y, ObjectLocation.Z);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

