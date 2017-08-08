// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Circuit.h"

//Circuit Log
DEFINE_LOG_CATEGORY(CircuitLog);

// Sets default values
ACircuit::ACircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACircuit::BeginPlay()
{
	Super::BeginPlay();

	// Reset time
	m_time = 0;
	m_timeIndex = 0;
	m_timeArray.Empty();
	m_bIsRunning = false;
}

// Called every frame
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Adds time
	if (m_bIsRunning) {
		m_time += DeltaTime;
		while (m_timeIndex < m_timeArray.Num() - 1 && m_timeArray[m_timeIndex + 1] < m_time) {
			m_timeIndex++;
		}

		// Stop simulation
		if (m_time >= 11) {
			m_bIsRunning = false;
			UE_LOG(CircuitLog, Warning, TEXT("Circuit: 11 seconds passed"));
		}
	}
}

// Adds component to the circuit
void ACircuit::AddComponent(AComponent *component)
{
	m_componentArray.Add(component);
	for (ACircNode *node : component->GetCircNodeArray()) {
		m_circNodeArray.Add(node);
	}
}

// Adds wires to the circuit
void ACircuit::AddWire(AWire *wire, ACircNode *circNode1, ACircNode *circNode2)
{
	m_componentArray.Add(wire);
	wire->AddCircNodes(circNode1, circNode2);
}

// Get array of components
TArray<AComponent*> ACircuit::GetComponentArray()
{
	return m_componentArray;
}

// Simulation commands
void ACircuit::Start()
{
	NgSpice &ngspice = NgSpice::getInstance();
	int32 m_componentCounter = 0;
	int32 m_circNodeCounter = 0;

	// Reset time and start simulation
	if (ngspice.AddCircuit(this)) {
		m_time = 0;
		m_timeIndex = 0;
		m_timeArray.Empty();
		m_bIsRunning = true;
		ngspice.Command("circbyline schema");
		for (ACircNode *circNode : m_circNodeArray) {
			circNode->ResetVoltageArray();
			circNode->SetId(m_circNodeCounter++);
		}
		for (AComponent *component : m_componentArray) {
			component->ResetCurrentArray();
			component->SetId(m_componentCounter++);
			UE_LOG(CircuitLog, Warning, TEXT("Circuit: %s"), *component->GetCircLine());
			ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline ") + component->GetCircLine())));
		}
		ngspice.Command("circbyline .end");
		ngspice.Command("tran 0.01 10 uic");
	}
}

// Updates results in components
void ACircuit::FillResults(pvecvaluesall data)
{
	for (int i = 0; i < data->veccount; i++) {
		if (data->vecsa[i]->name[1] == '(') {
			for (ACircNode *circNode : m_circNodeArray) {
				FString id = FString("V(") + FString::FromInt(circNode->GetId()) + FString(")");
				if (id.Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
					//UE_LOG(CircuitLog, Warning, TEXT("prave sa naplnil node s menom: %s\n"), *data->vecsa[i]->name);
					circNode->AddVoltage(data->vecsa[i]->creal);
				}
			}
		}
		else if (FString("time").Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
			m_timeArray.Add(data->vecsa[i]->creal);
		}
		else {
			for (AComponent *component : m_componentArray) {
				FString id = component->GetId() + FString("#branch");
				if (id.Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
					//UE_LOG(CircuitLog, Warning, TEXT("prave sa naplnil voltage dummy s menom: %s\n"), *data->vecsa[i]->name);
					component->AddCurrent(data->vecsa[i]->creal);
				}
			}
		}
	}
}

// Measure functions for multimeter
double ACircuit::MeasureCurrent(AWire *wire, float time) {
	if (time >= 10) {
		return wire->GetCurrent(m_timeArray.Num() - 1);
	}
	for (int i = 0; i < m_timeArray.Num() - 1; i++) {
		if (m_timeArray[i + 1] >= time) {
			return wire->GetCurrent(i);
		}
	}
	return 0;
}

double ACircuit::MeasureCurrent(AWire *wire) {
	return wire->GetCurrent(m_timeIndex);
}

double ACircuit::MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2, float time) {
	if (time >= 10) {
		return circNode1->GetVoltage(m_timeArray.Num() - 1) - circNode2->GetVoltage(m_timeArray.Num() - 1);
	}
	for (int i = 0; i < m_timeArray.Num() - 1; i++) {
		if (m_timeArray[i + 1] >= time) {
			return circNode1->GetVoltage(i) - circNode2->GetVoltage(i);
		}
	}
	return 0;
}

double ACircuit::MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2) {
	return circNode1->GetVoltage(m_timeIndex) - circNode2->GetVoltage(m_timeIndex);
}

void ACircuit::Report(const FString& report)
{
	UE_LOG(CircuitLog, Warning, TEXT("Report: %s"), *report);
}
