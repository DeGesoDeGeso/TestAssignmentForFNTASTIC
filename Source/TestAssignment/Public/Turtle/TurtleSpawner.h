

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turtle/TriggerInterface.h"
#include "TAEnum.h"
#include "TurtleSpawner.generated.h"

class UUsableComponent;
class ATurtleCharacter;
class UNiagaraSystem;
class USoundCue;

UCLASS()
class TESTASSIGNMENT_API ATurtleSpawner : public AActor, public ITriggerInterface
{
	GENERATED_BODY()
	
public:	
	ATurtleSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	UStaticMesh* StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UUsableComponent* ButtonComponent;

	UPROPERTY()
	UStaticMesh* ButtonMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* GateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Confetti;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Smoke;

	UPROPERTY()
	UStaticMesh* GateMesh;

	UPROPERTY()
	ATurtleCharacter* Turtle;

public:	
	UFUNCTION(BlueprintCallable)
	void SpawnTurtle();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger")
	void TriggerReact();

	virtual void TriggerReact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	EMovementType MovementType = EMovementType::MT_AlwaysForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	USkeletalMesh* AlternateTurtleSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVector TurtleMeshRelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FRotator TurtleMeshRelativeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	UAnimBlueprint* AlternateTurtleAnimBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	USoundCue* AlternatePoofCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	USoundCue* AlternateGoalCue;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	FVector GetGoalLocation() const;

private:
	FTransform DefineTurtleSpawnTransform() const;
	FVector DefineGoalLocation() const;

};
