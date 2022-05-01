


#include "Turtle/TurtleSpawner.h"
#include "UsableComponent.h"
#include "Turtle/TurtleCharacter.h"
#include "Turtle/TurtleAIController.h"

//TODO: Raycasted goal location

ATurtleSpawner::ATurtleSpawner()
{
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	ButtonComponent = CreateDefaultSubobject<UUsableComponent>("Button");
	ButtonComponent->SetupAttachment(StaticMeshComponent);

	GateComponent = CreateDefaultSubobject<UStaticMeshComponent>("GateMesh");
	GateComponent->SetupAttachment(StaticMeshComponent);
}

void ATurtleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ATurtleSpawner::SpawnTurtle()
{
	if(IsValid(Turtle))
	{
		auto CurrentController = Turtle->GetAIController();
		Turtle->UnPossessed();
		CurrentController->Destroy();
		Turtle->Destroy();
	}
	
	
	UWorld* World = GetWorld();
	if(!World || !ToSpawnTurtle)
		return;

	const FTransform SpawnTransform = CalculateTurtleSpawnTransform();
	ATurtleCharacter* CurrentTurtle = World->SpawnActorDeferred<ATurtleCharacter>(ToSpawnTurtle, SpawnTransform);

	if (!CurrentTurtle)
		return;
	
	CurrentTurtle->SetMovementType(MovementType);
	CurrentTurtle->GoalLocation = CalculateGoalLocation();
	CurrentTurtle->FinishSpawning(SpawnTransform);
	Turtle = CurrentTurtle;
	
}

void ATurtleSpawner::TriggerReact_Implementation()
{
	SpawnTurtle();
}


FTransform ATurtleSpawner::CalculateTurtleSpawnTransform() const
{
	FTransform TurtleTransform = StaticMeshComponent->GetComponentTransform();
	FVector Location = TurtleTransform.GetLocation();
	FQuat Rotation = TurtleTransform.GetRotation();
	Location = Location + Rotation.Vector() * -220;
	Location.Z += 10.0f;
	Rotation.Z += 180.0f;
	TurtleTransform.SetLocation(Location);
	TurtleTransform.SetRotation(Rotation);

	return TurtleTransform;

}

FVector ATurtleSpawner::CalculateGoalLocation() const
{
	FVector Location = GateComponent->GetComponentTransform().GetLocation();
	Location.Z -= 440;
	return  Location;
}

FVector ATurtleSpawner::GetGoalLocation() const
{
	return CalculateGoalLocation();
}
