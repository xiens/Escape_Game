// bububu

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveElevator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UMoveElevator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveElevator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressureDetector = nullptr;

	bool IsActorOnElevator();
	void StartElevator();

private:
	FVector StartingPosition;
	FVector CurrentPosition;
	FVector EndingPosition;
	//Platform's speed
	float Speed;
	bool GoingDown;
	bool StopElevator;
	bool AlreadyStopping;
	float ElevatorDelay;
	
	//void StopElevator();
	
	
};
