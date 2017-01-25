// Copyright Jack Cox 2017.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Called!"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector pos;
	FRotator rot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pos,rot);


	FVector traceEnd = pos + rot.Vector() * reach;
	DrawDebugLine(GetWorld(), pos, traceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
	//UE_LOG(LogTemp, Warning, TEXT("Position - %s. Rotation - %s."), *pos.ToString(), *rot.ToString());
}

