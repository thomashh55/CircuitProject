// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ngspice.h"
#include "CircNode.h"
#include "Component.h"

#include "Capacitor.h"
#include "Diode.h"
#include "Resistor.h"
#include "Transistor.h"
#include "VoltageSource.h"
#include "Wire.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Circuit.generated.h"

//Circuit Log
DECLARE_LOG_CATEGORY_EXTERN(CircuitLog, Log, All);

UCLASS()
class ACircuit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACircuit();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create circuit
	virtual void AddComponent(AComponent *component);
	virtual void AddWire(AWire *wire, ACircNode *circNode1, ACircNode *circNode2);

	// Get array of components
	virtual TArray<AComponent*> GetComponentArray();
	
	// Simulation commands
	virtual bool Start(float time);
	virtual float GetRealTime();
	virtual float GetSimulationTime();

	// Updates results in components
	virtual void FillResults(pvecvaluesall data);

	// Measure functions for multimeter
	virtual double MeasureCurrent(AWire *wire, float time);
	virtual double MeasureCurrent(AWire *wire);
	virtual double MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2, float time);
	virtual double MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2);

	// Debug purpose
	virtual void Report(const FString& report);

private:
	TArray<AComponent*> m_componentArray;
	TArray<ACircNode*> m_circNodeArray;

	TArray<double> m_timeArray;
	float m_endTime;
	float m_realTime;
	int m_realTimeIndex;
	bool m_bIsRunning;
	
};