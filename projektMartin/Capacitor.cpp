// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Capacitor.h"


// Sets default values
ACapacitor::ACapacitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
double ACapacitor::GetCapacitance()
{
	return m_capacitance;
}

void ACapacitor::SetCapacitance(double capacitance)
{
	m_capacitance = capacitance;
}

// Called when the game starts or when spawned
void ACapacitor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACapacitor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ACapacitor::GetPrefix()
{
	return "C";
}

