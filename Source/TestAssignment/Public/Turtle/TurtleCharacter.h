

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TAEnum.h"
#include "TurtleCharacter.generated.h"

class ATurtleAIController;
class UNiagaraSystem;
class USoundCue;

UCLASS(Blueprintable)
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

	UPROPERTY(BlueprintReadWrite, Category = "Movemet")
	FVector GoalLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxWalkSpeed = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationRate = 200;
	
	UFUNCTION(BlueprintCallable)
	ATurtleAIController* GetAIController() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMovementType(TEnumAsByte<EMovementType> ExternMovement);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool GetRestingCondition();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void OnGoal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Confetti;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Smoke;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	USoundCue* PoofSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	USoundCue* GoalSound;

	
protected:
	UPROPERTY()
	bool bIsResting = false;

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
	ATurtleAIController* CurrentAIController;

	UPROPERTY();
	UClass* AnimBlueprintClass;

};
