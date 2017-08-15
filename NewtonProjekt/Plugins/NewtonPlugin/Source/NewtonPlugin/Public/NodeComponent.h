// Martin Gulis & Tomas Liscak

#pragma once

#include "Component.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeComponent.generated.h"

UCLASS()
class NEWTONPLUGIN_API ANodeComponent : public AComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns NgSpice prefix
	virtual FString GetPrefix() override;

	// Returns line for NgSpice
	virtual FString GetCircLine() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
