// Martin Gulis & Tomas Liscak

#pragma once

#include "Ngspice.h"
#include "CircNode.h"
#include "Component.h"
#include "Wire.h"

#include "Capacitor.h"
#include "Diode.h"
#include "NodeComponent.h"
#include "Resistor.h"
#include "Transistor.h"
#include "VoltageSource.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Circuit.generated.h"

// Circuit Log
DECLARE_LOG_CATEGORY_EXTERN(CircuitLog, Log, All);

UCLASS()
class NEWTONPLUGIN_API ACircuit : public AActor
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

	// Initialize NgSpice
	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	static void Init();
	
	// Create circuit
	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual void AddComp(AComponent *component);

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual void RemoveComp(AComponent *component);

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual void AddWire(AWire *wire, ACircNode *circNode1, ACircNode *circNode2);

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual void RemoveWire(AWire *wire);

	// Get array of components and wires
	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual TArray<AComponent*> GetComponentArray();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual TArray<AWire*> GetWireArray();
	
	// Simulation commands
	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual bool Start(float endTime);

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual bool Stop();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual bool Resume();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual bool ForceStop();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual float GetRealTime();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual float GetSimulationTime();

	// Updates results in components
	virtual void FillResults(pvecvaluesall data);

	// Measure functions for multimeter
	/*UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual float MeasureCurrent(AWire *wire, float time);*/

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual float MeasureCurrent(AWire *wire);

	/*UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual float MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2, float time);*/

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual float MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2);

	// Finds error in circuit
	virtual void FillError(FString error);

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual ACircNode *GetErrorCircNode();

	UFUNCTION(BlueprintCallable, Category = "NewtonProject")
	virtual AWire *GetErrorWire();

	// Debug purpose
	virtual void Report(const FString& report);

private:
	TArray<AComponent*> m_componentArray;
	TArray<AWire*> m_wireArray;
	TArray<ACircNode*> m_circNodeArray;

	TArray<double> m_timeArray;
	float m_endTime;
	float m_realTime;
	int m_realTimeIndex;
	bool m_bIsRunning;

	ACircNode *m_errorCircNode;
	AWire *m_errorWire;
	
};
