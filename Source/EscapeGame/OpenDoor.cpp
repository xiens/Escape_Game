// bububu

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();



	//Find the owning actor
	Owner = GetOwner();
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float EscapeTime = 0.6f;

	//Open the door if total mass is equal to the mass of two chairs and a table
	if (GetTotalMassOfActorsOnPlate() == TriggerMass) {
		OnOpen.Broadcast(); //Open door
		//UE_LOG(LogTemp, Warning, TEXT("Last door open time is %f"), LastDoorOpenTime);
		//UE_LOG(TEXT(LogTemp, Warning, "LastDoorOpenTime = %f", LastDoorOpenTime));
	}

	else{
		OnClose.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	//Find all the overlapping actors
	TArray<AActor*> OverlappingActors1;
	TArray<AActor*> OverlappingActors2;
	TArray<AActor*> OverlappingActors3;

	if (!PressurePlate) { return TotalMass; }
	if (!PressurePlate2) { return TotalMass; }
	if (!PressurePlate3) { return TotalMass; }

	PressurePlate->GetOverlappingActors(OUT OverlappingActors1);
	PressurePlate2->GetOverlappingActors(OUT OverlappingActors2);
	PressurePlate3->GetOverlappingActors(OUT OverlappingActors3);
	
	//Iterate throuugh them adding their masses
	for (auto& OverlappedActor : OverlappingActors1) {
		//UE_LOG(LogTemp, Warning, TEXT("Actor on plate is %s"), *OverlappedActor->GetName());
		TotalMass += OverlappedActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Total mass on plate is %f"), TotalMass);
	}

	for (auto& OverlappedActor : OverlappingActors2) {
		TotalMass += OverlappedActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	for (auto& OverlappedActor : OverlappingActors3) {
		TotalMass += OverlappedActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}


