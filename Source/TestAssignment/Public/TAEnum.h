#pragma once

#include "TAEnum.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	MT_AlwaysForward		UMETA(DisplayName = "Always Forward"),
	MT_ForwardThenStop		UMETA(DisplayName = "Forward And Stop"),
	MT_ForwardThenBack		UMETA(DisplayName = "Forward And Back")
};