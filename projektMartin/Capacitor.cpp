// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Capacitor.h"


const FString ACapacitor::m_prefix = FString("C");

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
	return m_prefix;
}

FString ACapacitor::GetCircLine()
{
	/*if (m_nodeArray[0] != NULL && m_nodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_nodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_nodeArray[1]->GetId()) + FString(" ") +
			FString::SanitizeFloat(m_capacitance);
	}*/
	return FString();
}

