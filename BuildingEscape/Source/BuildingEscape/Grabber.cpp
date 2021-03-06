// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	///Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physics handle found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component."),*GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Get player view point
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	//TODO Log Out to test
	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString());*/
	
	FVector LineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()*Reach;
	
	///Draw a red trace line
	DrawDebugLine(GetWorld(), playerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.0f);
	
	///Line-cast out to reach distance
	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT(" ")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		playerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	//See what we hit
	AActor* hitActor = Hit.GetActor();
	if (hitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit :%s"), *hitActor->GetName());
	}

}

