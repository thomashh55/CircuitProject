// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Circuit.h"
#include "GameFramework/Actor.h"
#include "Tester.generated.h"

//Tester Log
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
	ACircuit *circuit;
	AVoltageSource *voltageSource1;
	AResistor *resistor1;
	AResistor *resistor2;
	AResistor *resistor3;
	AWire *wire1;
	AWire *wire2;
	AWire *wire3;
	AWire *wire4;

};
