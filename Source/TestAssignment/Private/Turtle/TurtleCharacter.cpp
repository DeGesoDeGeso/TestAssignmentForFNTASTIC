


#include "Turtle/TurtleCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Turtle/TurtleAIController.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

//TODO: rewrite with OnPossess

ATurtleCharacter::ATurtleCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	PoofAudioComponent = CreateDefaultSubobject<UAudioComponent>("PoofAudioComponent");
	PoofAudioComponent->SetupAttachment(GetRootComponent());

	GoalAudioComponent = CreateDefaultSubobject<UAudioComponent>("GoalAudioComponent");
	GoalAudioComponent->SetupAttachment(GetRootComponent());

	GetCapsuleComponent()->SetCapsuleHalfHeight(34.0f);
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ATurtleAIController::StaticClass();


}

void ATurtleCharacter::BeginPlay()
{
	Super::BeginPlay();

	UCharacterMovementComponent* CurrentMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	AController* CurrentController = GetController();
	CurrentAIController = Cast<ATurtleAIController>(CurrentController);
	if(!CurrentMovementComponent || !CurrentAIController)
		return;
	
	bUseControllerRotationYaw = false;
	MovementComponent = CurrentMovementComponent;
	MovementComponent->bUseControllerDesiredRotation = true;
	MovementComponent->RotationRate.Yaw = RotationRate;
	MovementComponent->MaxWalkSpeed = MaxWalkSpeed;
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Smoke, GetActorLocation());
	
	WalkForward();
}

void ATurtleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATurtleCharacter::Jump);
	PlayerInputComponent->BindAxis("LookUp", this, &ATurtleCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATurtleCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATurtleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATurtleCharacter::MoveRight);
}

void ATurtleCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ATurtleCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

ATurtleAIController* ATurtleCharacter::GetAIController() const
{
	return CurrentAIController;
}

void ATurtleCharacter::WalkForward()
{
	if (!GetWorld() || !CurrentAIController)
		return;

	MovementComponent->MaxWalkSpeed = MaxWalkSpeed;
	CurrentAIController->BeginMoveTo(GoalLocation);

	switch (MovementType)
	{
	case EMovementType::MT_AlwaysForward:
		{
			GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ATurtleCharacter::WalkForward, 1.f, true);
		}
		break;
	case EMovementType::MT_ForwardThenBack:
		{
			GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ATurtleCharacter::WalkBackward, 1.f, true);
		}
		break;
		
	case EMovementType::MT_ForwardThenStop:
		{
			GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ATurtleCharacter::WalkStop, 1.f, true);
		}
		break;
	}
		
}

void ATurtleCharacter::WalkBackward()
{
	if(!GetWorld() || !CurrentAIController)
		return;
	CurrentAIController->WalkBackward();
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ATurtleCharacter::WalkForward, 0.5f, true);
}

void ATurtleCharacter::WalkStop()
{
	if (!GetWorld() || !CurrentAIController)
		return;

	MovementComponent->MaxWalkSpeed = 0.f;
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ATurtleCharacter::WalkForward, 0.5f, true);
}

float ATurtleCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
		return 0.f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return  CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ATurtleCharacter::SetMovementType(TEnumAsByte<::EMovementType> Movement)
{
	MovementType = Movement;
}

void ATurtleCharacter::OnGoal()
{
	if (!GetWorld())
		return;
	if(!bIsResting)
	{

		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		const FVector EmitterLocation = GetActorLocation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Confetti, EmitterLocation);
		
		GoalAudioComponent->Play();
	}

	bIsResting = true;
}

bool ATurtleCharacter::GetRestingCondition()
{
	return bIsResting;
}

