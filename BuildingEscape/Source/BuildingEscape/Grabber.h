// Copyright Sean Avila 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();

	// Return the first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	// Return the line trace end
	FVector GetPlayersReach() const;

	// Get Players position in the world
	FVector GetPlayersWorldPos() const;

private:
	float Reach = 100.f;
	UPROPERTY()
		UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
		UInputComponent* InputComponent = nullptr;
};
