// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Resistor.h"


// Sets default values
AResistor::AResistor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
double AResistor::GetResistance()
{
	return m_resistance;
}

void AResistor::SetResistance(double resistance)
{
	m_resistance = resistance;
}

// Called when the game starts or when spawned
void AResistor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResistor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AResistor::GetPrefix()
{
	return "R";
}

