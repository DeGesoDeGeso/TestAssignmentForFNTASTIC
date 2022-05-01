


#include "Turtle/TurtleSpawner.h"
#include "UsableComponent.h"
#include "Turtle/TurtleCharacter.h"
#include "Turtle/TurtleAIController.h"

//TODO: Raycasted goal location

ATurtleSpawner::ATurtleSpawner()
{
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/Assets/World/Kennel.Kennel'"));
	StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);

	ButtonComponent = CreateDefaultSubobject<UUsableComponent>("Button");
	ButtonComponent->SetupAttachment(StaticMeshComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonMeshAsset(TEXT("StaticMesh'/Game/Assets/World/Button.Button'"));
	ButtonComponent->SetStaticMesh(ButtonMeshAsset.Object);

	GateComponent = CreateDefaultSubobject<UStaticMeshComponent>("GateMesh");
	GateComponent->SetupAttachment(StaticMeshComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshAsset(TEXT("StaticMesh'/Game/Assets/World/Gate.Gate'"));
	GateComponent->SetStaticMesh(GateMeshAsset.Object);	
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
	
	const FTransform SpawnTransform = DefineTurtleSpawnTransform();
	UWorld* World = GetWorld();
	if(!World)
		return;
	
	ATurtleCharacter* CurrentTurtle = World->SpawnActorDeferred<ATurtleCharacter>(ATurtleCharacter::StaticClass(), SpawnTransform);
	if(!CurrentTurtle)
		return;
	
	CurrentTurtle->SetMovementType(MovementType);
	CurrentTurtle->SetGoalLocation(DefineGoalLocation());
	CurrentTurtle->SetNiagaraSystems(Confetti, Smoke);
	CurrentTurtle->SetSkeletalMesh(AlternateTurtleSkeletalMesh, AlternateTurtleAnimBlueprint, TurtleMeshRelativeLocation, TurtleMeshRelativeRotation);
	CurrentTurtle->SetGoalSound(AlternateGoalCue);
	CurrentTurtle->SetPoofSound(AlternatePoofCue);
	CurrentTurtle->FinishSpawning(SpawnTransform);
	Turtle = CurrentTurtle;
	
}

void ATurtleSpawner::TriggerReact_Implementation()
{
	SpawnTurtle();
}


FTransform ATurtleSpawner::DefineTurtleSpawnTransform() const
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

FVector ATurtleSpawner::DefineGoalLocation() const
{
	FVector Location = GateComponent->GetComponentTransform().GetLocation();
	Location.Z -= 440;
	return  Location;
}

FVector ATurtleSpawner::GetGoalLocation() const
{
	return DefineGoalLocation();
}
