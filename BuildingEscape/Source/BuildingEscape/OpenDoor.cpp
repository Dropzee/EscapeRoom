// Copyright Jack Cox 2017.

#include "BuildingEscape.h"
#include "OpenDoor.h"


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
	owner = GetOwner();
}


void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.f, openAngle, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float mass = 0.f;
	TArray<AActor*> actors;
	pressurePlate->GetOverlappingActors(actors);
	for(const auto* a : actors){
		mass += a->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	if (mass > 100.f) {
		OpenDoor();
		lastOpenTime = GetWorld()->GetTimeSeconds();
	}

	if(GetWorld()->GetTimeSeconds() - lastOpenTime >= doorCloseDelay) {
		CloseDoor();
	}

}

