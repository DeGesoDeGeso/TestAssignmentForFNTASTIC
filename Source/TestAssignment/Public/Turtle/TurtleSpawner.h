

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turtle/TriggerInterface.h"
#include "TAEnum.h"
#include "TurtleSpawner.generated.h"

class UUsableComponent;
class ATurtleCharacter;
class USoundCue;

UCLASS(Blueprintable)
class TESTASSIGNMENT_API ATurtleSpawner : public AActor, public ITriggerInterface
{
	GENERATED_BODY()
	
public:	
	ATurtleSpawner();

protected:
	virtual void BeginPlay() override;
	



	UPROPERTY()
	ATurtleCharacter* Turtle;

public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UUsableComponent* ButtonComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GateComponent;
	
	
	UFUNCTION(BlueprintCallable)
	void SpawnTurtle();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger")
	void TriggerReact();

	virtual void TriggerReact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class ATurtleCharacter> ToSpawnTurtle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	EMovementType MovementType = EMovementType::MT_AlwaysForward;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	FVector GetGoalLocation() const;

private:
	FTransform CalculateTurtleSpawnTransform() const;
	FVector CalculateGoalLocation() const;

};
