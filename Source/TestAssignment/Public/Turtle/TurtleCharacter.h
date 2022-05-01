

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TAEnum.h"
#include "TurtleCharacter.generated.h"

class ATurtleAIController;
class UNiagaraSystem;
class USoundCue;

UCLASS()
class TESTASSIGNMENT_API ATurtleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATurtleCharacter();

protected:
	virtual void BeginPlay() override;

	void MoveRight(float Amount);
	void MoveForward(float Amount);

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxWalkSpeed = 400;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsResting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Confetti;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Smoke;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	USoundCue* PoofSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	USoundCue* GoalSound;
	
	UFUNCTION(BlueprintCallable)
	ATurtleAIController* GetAIController() const;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetGoalLocation(const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector GetGoalLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMovementType(TEnumAsByte<EMovementType> ExternMovement);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool GetRestingCondition();
	
	UFUNCTION(BlueprintCallable)
	void SetNiagaraSystems(UNiagaraSystem* Confettir, UNiagaraSystem* Smoker);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void OnGoal();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SetSkeletalMesh(USkeletalMesh* SkeletalMesh, UAnimBlueprint* AnimBlueprint, FVector RelativeLocation = FVector::ZeroVector, FRotator RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SetGoalSound(USoundCue* GoalCue);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SetPoofSound(USoundCue* PoofCue);
	
protected:
	UPROPERTY()
	FVector GoalLocation;


	UFUNCTION(BlueprintCallable, Category = "Movement")
	void WalkForward();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void WalkBackward();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void WalkStop();
	
	FTimerHandle MovementTimerHandle;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	EMovementType MovementType = EMovementType::MT_AlwaysForward;

private:
	UPROPERTY()
	UAudioComponent* PoofAudioComponent;

	UPROPERTY()
	UAudioComponent* GoalAudioComponent;

	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY()
	USkeletalMesh* AlternateSkeletalMesh;

	UPROPERTY()
	UAnimBlueprint* AlternateAnimBlueprint;

	UPROPERTY()
	USoundCue* AlternatePoofCue;

	UPROPERTY()
	USoundCue* AlternateGoalCue;

	UPROPERTY()
	ATurtleAIController* CurrentAIController;

	UPROPERTY();
	UClass* AnimBlueprintClass;

};
