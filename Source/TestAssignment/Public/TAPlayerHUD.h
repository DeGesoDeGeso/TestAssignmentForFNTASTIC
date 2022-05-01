#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TAPlayerHUD.generated.h"

UCLASS()
class TESTASSIGNMENT_API ATAPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();
};
