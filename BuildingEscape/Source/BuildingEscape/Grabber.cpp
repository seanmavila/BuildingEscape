// Copyright Sean Avila 2022

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Get line showing reach
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed!"));

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Get line showing reach
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	// If hit, attatch the physics handle
	// TODO attach physics handle
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
	}
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released!"));

	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics handle component found on %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;	

	// Get line showing reach
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;


	/*DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);*/

	FHitResult Hit;
	// Raycast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what raycast hits
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		// Logging out to test
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *ActorHit->GetName());

	}
	return Hit;
}

