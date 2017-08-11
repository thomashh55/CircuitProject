// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"

#include "Capacitor.h"


const FString ACapacitor::m_prefix = FString("C");

// Sets default values
ACapacitor::ACapacitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_capacitance = 0;
	m_initVoltage = 0;
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

double ACapacitor::GetInitVoltage()
{
	return m_initVoltage;
}

void ACapacitor::SetInitVoltage(double initVoltage)
{
	m_initVoltage = initVoltage;
}

// Called when the game starts or when spawned
void ACapacitor::BeginPlay()
{
	Super::BeginPlay();

	// Create nodes
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
}

// Called every frame
void ACapacitor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns NgSpice prefix
FString ACapacitor::GetPrefix()
{
	return m_prefix;
}

// Returns line for NgSpice
FString ACapacitor::GetCircLine()
{
	if (m_circNodeArray.Num() == 2 && m_circNodeArray[0] != NULL && m_circNodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_circNodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[1]->GetId()) + FString(" ") +
			FString::SanitizeFloat(m_capacitance) + FString(" ic=") + 
			FString::FromInt(m_initVoltage) + FString("V");
	}
	return FString();
}

