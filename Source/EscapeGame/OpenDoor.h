// bububu

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate2 = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate3 = nullptr;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:

	UPROPERTY(EditAnywhere)
	float TriggerMass = 80.f; //2 x 20kg for chairs and 40kg for table
	//Owning Door
	AActor* Owner;
	
	//Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
