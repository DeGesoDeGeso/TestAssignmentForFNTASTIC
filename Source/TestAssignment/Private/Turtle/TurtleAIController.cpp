
#include "Turtle/TurtleAIController.h"
#include "TurtleCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(AILog, All, All);

ATurtleAIController::ATurtleAIController()
{
}

void ATurtleAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATurtleAIController::BeginMoveTo(const FVector Location)
{
	ClearFocus(EAIFocusPriority::Gameplay);
	
	const auto Result = MoveToLocation(Location, 50.0f, false, true);
	if(Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{

		ATurtleCharacter* Turtle = Cast<ATurtleCharacter>(GetInstigator());
		if (Turtle)
			Turtle->OnGoal();
	}
	
}

void ATurtleAIController::WalkBackward()
{
	const ATurtleCharacter* Turtle = Cast<ATurtleCharacter>(GetInstigator());
	if (!Turtle)
		return;
	const FVector FocalPoint = GetFocalPoint();
	SetFocalPoint(FocalPoint, EAIFocusPriority::Gameplay);
	const FVector NewLocation = (FocalPoint - Turtle->GetActorLocation()) * -200.f;
	MoveToLocation(NewLocation, 0, true, false);
}

