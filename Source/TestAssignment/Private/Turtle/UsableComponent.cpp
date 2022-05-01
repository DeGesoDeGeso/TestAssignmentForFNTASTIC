


#include "Turtle/UsableComponent.h"
#include "Turtle/TurtleSpawner.h"
#include "Turtle/TriggerInterface.h"

void UUsableComponent::Interact()
{
	if (!GetOwner())
		return;
	AActor* Object = GetOwner();
	const bool bIsImplemented = Object->Implements<UTriggerInterface>();
	if(bIsImplemented)
	{
		ITriggerInterface::Execute_TriggerReact(Object);
	}
}
