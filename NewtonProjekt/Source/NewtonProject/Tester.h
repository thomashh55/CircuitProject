// Martin Gulis & Tomas Liscak

#pragma once

#include "Circuit.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tester.generated.h"

// Tester Log
DECLARE_LOG_CATEGORY_EXTERN(TesterLog, Log, All);

UCLASS()
class NEWTONPROJECT_API ATester : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PressedY();
	virtual void PressedU();
	virtual void PressedI();
	virtual void PressedO();
	virtual void PressedP();

	virtual void PressedG();
	virtual void PressedH();
	virtual void PressedJ();
	virtual void PressedK();
	virtual void PressedL();

	virtual void PressedC();
	virtual void PressedV();
	virtual void PressedB();
	virtual void PressedN();
	virtual void PressedM();

private:

	// Serial resistors test
	ACircuit *t0_circuit;
	AVoltageSource *t0_voltageSource1;
	AResistor *t0_resistor1;
	AResistor *t0_resistor2;
	AResistor *t0_resistor3;
	AWire *t0_wire1;
	AWire *t0_wire2;
	AWire *t0_wire3;
	AWire *t0_wire4;

	// Schema 1 test
	ACircuit *t1_circuit;
	AVoltageSource *t1_voltageSource1;
	ADiode *t1_diode1;
	ADiode *t1_diode2;
	AResistor *t1_resistor1;
	AResistor *t1_resistor2;
	AResistor *t1_resistor3;
	AResistor *t1_resistor4;
	ACapacitor *t1_capacitor1;
	ACapacitor *t1_capacitor2;
	ATransistor *t1_transistor1;
	ATransistor *t1_transistor2;
	AWire *t1_wire1;
	AWire *t1_wire2;
	AWire *t1_wire3;
	AWire *t1_wire4;
	AWire *t1_wire5;
	AWire *t1_wire6;
	AWire *t1_wire7;
	AWire *t1_wire8;
	AWire *t1_wire9;
	AWire *t1_wire10;
	AWire *t1_wire11;
	AWire *t1_wire12;
	AWire *t1_wire13;
	AWire *t1_wire14;
	AWire *t1_wire15;
	AWire *t1_wire16;

	// Wrong component test
	ACircuit *t2_circuit;
	AVoltageSource *t2_voltageSource1;
	AResistor *t2_resistor1;
	AResistor *t2_resistor2;
	ANodeComponent *t2_nodeComponent1;
	AWire *t2_wire1;
	AWire *t2_wire2;
	AWire *t2_wire3;
	AWire *t2_wire4;
	AWire *t2_wire5;

};
