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

	//

	handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!handle) {
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s!"), *(GetOwner()->GetName()));
	}

	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input) {
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input not found on %s!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"));
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

	FHitResult traceHit;
	FCollisionQueryParams params(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(traceHit, pos, traceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), params);

	AActor* actorHit = traceHit.GetActor();
	if (actorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Trace hit - %s"), *(actorHit->GetName()))
	}

}

