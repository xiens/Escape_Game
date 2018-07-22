
// bububu

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//How far can we reach in cm
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UInputComponent* Input = nullptr;
	
	//Rat-cast and grab what's in reach
	void Grab();
	//Release whatever is grabbed
	void Release();

	//Find and setup (assumed) input component
	void FindInputComponent();
	//Find attached physics handle
	void FindPhysicsHandleComponent();

	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInreach();

	//Calculate the start of line trace 
	FVector CalculateLineTraceStart();

	//Calculate the end of line trace 
	FVector CalculateLineTraceEnd();
};
