// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ngspice.h"
#include "CircNode.h"
#include "Component.h"
#include "Resistor.h"
#include "VoltageSource.h"
#include "GameFramework/Actor.h"
#include "Circuit.generated.h"

//Circuit Log
DECLARE_LOG_CATEGORY_EXTERN(CircuitLog, Log, All);

UCLASS()
class NEWTONPROJECT_API ACircuit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACircuit();

	// Getters and Setters
	/*TArray<AComponent*> GetComponentArray();
	void SetComponentArray(TArray<AComponent*> componentArray);
	TArray<ACircNode*> GetCircNodeArray();
	void SetCircNodeArray(TArray<ACircNode*> circNodeArray);*/
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create circuit
	virtual void AddComponent(AComponent *component);
	virtual void AddNode(ACircNode *circNode);
	
	// Simulation commands
	virtual void Start();
	virtual void Command(char *command);

private:
	TArray<AComponent*> m_componentArray;
	TArray<ACircNode*> m_circNodeArray;
	
};
