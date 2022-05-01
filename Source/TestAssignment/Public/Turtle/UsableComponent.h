

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "UsableComponent.generated.h"


UCLASS(Blueprintable)
class TESTASSIGNMENT_API UUsableComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Interact();
};
