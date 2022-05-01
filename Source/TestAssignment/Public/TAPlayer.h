

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TAPlayer.generated.h"

UCLASS()
class TESTASSIGNMENT_API ATAPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ATAPlayer();

protected:
	virtual void BeginPlay() override;
	
	void MoveRight(float Amount);
	void MoveForward(float Amount);
	void Interact();
	
public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0"))
	float InteractDistance = 400;

private:


};
