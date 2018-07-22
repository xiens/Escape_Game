// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//InitialPosition = GetOwner()->GetTargetLocation();
	MoveLeft = true;
	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	
	FString objectName;
	FString objectPos = GetOwner()->GetTargetLocation().ToString();
	FString objectPos2 = GetOwner()->GetTransform().GetLocation().ToString();

	objectName = GetOwner()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *objectName, *objectPos2);
	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//move chair
	//if (MoveLeft) {
	//	if (GetOwner()->GetTargetLocation().X < -150.f && GetOwner()->GetTargetLocation().X > -400.f) {
	//		GetOwner()->SetActorLocation(InitialPosition - FVector(1.f, 0.f, 0.f));
	//	}
	//	else {
	//		MoveLeft = false;
	//	}
	//}

	//if (!MoveLeft) {
	//	GetOwner()->SetActorLocation(InitialPosition);
	//	MoveLeft = true;
	//}
	// ...
}

