// Martin Gulis & Tomas Liscak

#pragma once

#include "Component.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoltageSource.generated.h"

UCLASS()
class NEWTONPLUGIN_API AVoltageSource : public AComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoltageSource();

	// Getters and Setters
	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	float GetDirectCurrent();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	void SetDirectCurrent(float directCurrent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns NgSpice prefix
	virtual FString GetPrefix() override;

	// Returns line for NgSpice
	virtual FString GetCircLine() override;

private:
	static const FString m_prefix;
	double m_directCurrent;
	
};
