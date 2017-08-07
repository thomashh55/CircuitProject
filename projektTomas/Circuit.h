// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircNode.h"
#include "Component.h"
#include "Resistor.h"
#include "VoltageSource.h"
#include "Wire.h"
#include "ngspice.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ngspice/dvec.h"
#include "Circuit.generated.h"

//Circuit Log
//DECLARE_LOG_CATEGORY_EXTERN(CircuitLog, Log, All);

UCLASS()
class MYPROJECT2_API ACircuit : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACircuit();
	~ACircuit();
	float time;

	static TArray<AComponent*> m_componentArray;
	static TArray<ACircNode*> m_circNodeArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called before destroing the actor
	virtual void BeginDestroy() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create circuit
	virtual void AddComponent(AComponent *component);
	virtual void AddWire(AWire *wire, ACircNode *circNode1, ACircNode *circNode2);

	// Get array of components
	virtual TArray<AComponent*> GetComponentArray();

	// Simulation commands
	virtual void Start();

	// Debug purpose
	virtual void Report(const FString& report);

	// Measure functions for multimeter
	float MeasureCurrent(AWire wire, float time);
	float MeasureCurrent(AWire wire);
	float MeasureVoltage(ACircNode node, float time);
	float MeasureVoltage(ACircNode node);

};