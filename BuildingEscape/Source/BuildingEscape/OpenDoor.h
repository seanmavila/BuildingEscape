// Copyright Sean Avila 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
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
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindAudioComponent();
	void FindPressurePlate();
	float TotalMassOfActors() const;

private:
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

	// Tracks if sound has been played
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere)
		float TargetYaw = -90.;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.f;

	UPROPERTY(EditAnywhere)
		float MassToOpenDoor = 50.f;

	
	
};
