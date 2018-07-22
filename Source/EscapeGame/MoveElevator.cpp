// bububu

#include "MoveElevator.h"
#include"TimerManager.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UMoveElevator::UMoveElevator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveElevator::BeginPlay()
{
	Super::BeginPlay();
	StartingPosition = GetOwner()->GetActorLocation();
	CurrentPosition = StartingPosition;
	EndingPosition = FVector(608.f, 420.f, 1227.f);
	Speed = 3.f;
	ElevatorDelay = 3.f;
	GoingDown = false;
	StopElevator = true;
	AlreadyStopping = true;

	
	
	
	// ...
	
}




// Called every frame
void UMoveElevator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector delta = FVector(0.0f, 0.0f, Speed);
	
	if (IsActorOnElevator()) {
		FTimerHandle UnusedHandle;
		
		if (CurrentPosition.Z >= EndingPosition.Z || CurrentPosition.Z == StartingPosition.Z) {
			
			StopElevator = true;
			
			GetWorld()->GetTimerManager().SetTimer(
				UnusedHandle, this, &UMoveElevator::StartElevator, ElevatorDelay, false);
			if (GoingDown) {
				CurrentPosition -= delta;
				UE_LOG(LogTemp, Warning, TEXT("Going down current position is, %f"), CurrentPosition.Z);
			}
			else {
				CurrentPosition += delta;
				UE_LOG(LogTemp, Warning, TEXT("Going up current position is, %f"), CurrentPosition.Z);
			}
		}
		
		
		if (CurrentPosition.Z >= EndingPosition.Z) {
			
			GoingDown = true; //Now it's going down
			//add delay here
			//StopElevator = true;

		}

		if (GoingDown) {
				if(!StopElevator) CurrentPosition -= delta;
				if (CurrentPosition.Z <= StartingPosition.Z) {
					GoingDown = false; //Now it's going up
					//add delay here
					//StopElevator = true;
				}
		}
		else {
			if (!StopElevator) CurrentPosition += delta;

		}
		GetOwner()->SetActorLocation(CurrentPosition); //Move the elevator every frame

	}
}

void UMoveElevator::StartElevator() {
	if (IsActorOnElevator()) {
		StopElevator = false;
		UE_LOG(LogTemp, Warning, TEXT("Holding the elevator"));
	}
	//FVector delta = FVector(0.0f, 0.0f, Speed);
	
		//GetOwner()->SetActorLocation(CurrentPosition);
}

bool UMoveElevator::IsActorOnElevator()
{
	if (!PressureDetector) { return false; }
	TArray<AActor*> OverlappingActors;
	PressureDetector->GetOverlappingActors(OUT OverlappingActors);
	if (OverlappingActors.Num() > 0) { //Check if any actor is on the elevator
		return true;
	}
	else return false;
}

