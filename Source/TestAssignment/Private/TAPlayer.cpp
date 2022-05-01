

#include "TAPlayer.h"
#include "Turtle/UsableComponent.h"


ATAPlayer::ATAPlayer()
{
 
	PrimaryActorTick.bCanEverTick = false;

}

void ATAPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATAPlayer::Jump);
	PlayerInputComponent->BindAxis("LookUp", this, &ATAPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATAPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATAPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATAPlayer::MoveRight);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ATAPlayer::Interact);
}

void ATAPlayer::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ATAPlayer::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ATAPlayer::Interact()
{
	FVector ViewLocation;
	FRotator ViewRotation;
	FHitResult HitResult;
	APlayerController* CurrentPlayerController = GetController<APlayerController>();
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bReturnFaceIndex = true;
	
	if(!CurrentPlayerController)
		return;

	CurrentPlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	const FVector TraceStart = ViewLocation;
	const FVector& TraceEnd = ViewLocation + ViewRotation.Vector() * InteractDistance;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
	UPrimitiveComponent* ReceivedComponent = HitResult.GetComponent();
	
	if (!ReceivedComponent)
		return;
	
	UUsableComponent* UsableComponent = Cast<UUsableComponent>(ReceivedComponent);
	if (UsableComponent)
	{
		UsableComponent->Interact();
	}
}
