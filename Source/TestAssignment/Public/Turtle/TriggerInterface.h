

#pragma once

#include "TriggerInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UTriggerInterface : public UInterface
{
    GENERATED_BODY()
};

class TESTASSIGNMENT_API ITriggerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger")
    void TriggerReact();
};