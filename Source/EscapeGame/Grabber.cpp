// bububu

#include "Grabber.h"
#include "Engine/World.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Look for physics handle
	FindPhysicsHandleComponent();
	// Look for attached Input component (only appears at run time)
	FindInputComponent();

}

void UGrabber::FindInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input) {
		//Found input component
		UE_LOG(LogTemp, Warning, TEXT("Found input component"));
		//Bind the input axis
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No input component found for pawn: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		//Physics handle is found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No physics component found for pawn: %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	FVector LineTraceEnd = CalculateLineTraceEnd();
	//If the physics handle is attached -> move the object that we're holding
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

	//LINE TRACE to reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInreach();
	auto GrabbedComponent = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	//If we hit something then attach a physics handle
	if (ActorHit) {
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			GrabbedComponent,
			NAME_None, //don't need bones
			GrabbedComponent->GetOwner()->GetActorLocation(),
			GrabbedComponent->GetOwner()->GetActorRotation()
		);
	}

}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Object released"));
	//Release physics handle
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInreach()
{
	FVector PlayerViewPointLocation = CalculateLineTraceStart();
	FVector LineTraceEnd = CalculateLineTraceEnd();

	//Draw a red trace in world to visualize
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 5.f);

	///Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); //ignore details in objects, and ourselves
																	   
	FHitResult LineTraceHit;
	//Ray-cast out to reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* actorHit;
	actorHit = LineTraceHit.GetActor();

	//See what we hit
	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("we hit actor: %s"), *(actorHit->GetName()));
	}

	return LineTraceHit;
}
FVector UGrabber::CalculateLineTraceStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	//This method sets the player view point parameters
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UGrabber::CalculateLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	//This method sets the player view point parameters
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

