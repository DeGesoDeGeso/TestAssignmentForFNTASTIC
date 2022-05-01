

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurtleAIController.generated.h"


UCLASS()
class TESTASSIGNMENT_API ATurtleAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATurtleAIController();

	void BeginMoveTo(const FVector Location);

	void WalkBackward();
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	FAIMoveRequest GoalLocation;

	
};
