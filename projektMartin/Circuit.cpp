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
	m_timeArray.Empty();
	m_endTime = 0;
	m_realTime = 0;
	m_realTimeIndex = 0;
	m_bIsRunning = false;
}

// Called every frame
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Adds time
	if (m_bIsRunning) {
		m_realTime += DeltaTime;
		while (m_realTimeIndex < m_timeArray.Num() - 1 && m_timeArray[m_realTimeIndex + 1] <= m_realTime) {
			m_realTimeIndex++;
			//UE_LOG(CircuitLog, Warning, TEXT("Circuit: Time: %f ArrayTime: %f index: %d"), m_realTime, m_timeArray[m_realTimeIndex], m_realTimeIndex);
		}

		// Stop simulation
		if (m_realTime >= m_endTime) {
			m_bIsRunning = false;
			UE_LOG(CircuitLog, Warning, TEXT("Circuit: %f seconds passed"), m_endTime);
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
bool ACircuit::Start(float time)
{
	NgSpice &ngspice = NgSpice::getInstance();
	int m_componentCounter = 0;
	int m_circNodeCounter = 0;

	if (time < 0) {
		time = 0;
	}

	// Reset time and start simulation
	bool bCanRun = ngspice.AddCircuit(this, time);
	if (bCanRun) {
		m_timeArray.Empty();
		m_endTime = time;
		m_realTime = 0;
		m_realTimeIndex = 0;
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
		ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline .tran ") + 
			FString::SanitizeFloat(time / 1000) + FString(" ") + 
			FString::SanitizeFloat(time) + FString(" uic"))));
		ngspice.Command("circbyline .end");
		ngspice.Command("bg_run");
		/*ngspice.Command(TCHAR_TO_ANSI(*(FString("tran ") + 
			FString::SanitizeFloat(time / 10) + FString(" ") + 
			FString::SanitizeFloat(time) + FString(" uic"))));*/
	}
	return bCanRun;
}

float ACircuit::GetRealTime()
{
	return m_realTime;
}

float ACircuit::GetSimulationTime()
{
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	return m_timeArray[m_realTimeIndex];
}

// Updates results in components
void ACircuit::FillResults(pvecvaluesall data)
{
	UE_LOG(CircuitLog, Warning, TEXT("Circuit: data %d arrived"), data->vecindex);
	for (int i = 0; i < data->veccount; i++) {
		if (data->vecsa[i]->name[1] == '(') {
			for (ACircNode *circNode : m_circNodeArray) {
				FString id = FString("V(") + FString::FromInt(circNode->GetId()) + FString(")");
				if (id.Equals(data->vecsa[i]->name, ESearchCase::IgnoreCase)) {
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
					component->AddCurrent(data->vecsa[i]->creal);
				}
			}
		}
	}
}

// Measure functions for multimeter
double ACircuit::MeasureCurrent(AWire *wire, float time) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	for (int i = 0; i < m_timeArray.Num() - 1; i++) {
		if (m_timeArray[i + 1] > time) {
			return wire->GetCurrent(i);
		}
	}
	return wire->GetCurrent(m_timeArray.Num() - 1);
}

double ACircuit::MeasureCurrent(AWire *wire) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	return wire->GetCurrent(m_realTimeIndex);
}

double ACircuit::MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2, float time) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	for (int i = 0; i < m_timeArray.Num() - 1; i++) {
		if (m_timeArray[i + 1] > time) {
			return circNode1->GetVoltage(i) - circNode2->GetVoltage(i);
		}
	}
	return circNode1->GetVoltage(m_timeArray.Num() - 1) - circNode2->GetVoltage(m_timeArray.Num() - 1);
}

double ACircuit::MeasureVoltage(ACircNode *circNode1, ACircNode *circNode2) {
	if (m_timeArray.Num() == 0) {
		return 0;
	}
	return circNode1->GetVoltage(m_realTimeIndex) - circNode2->GetVoltage(m_realTimeIndex);
}

void ACircuit::Report(const FString& report)
{
	UE_LOG(CircuitLog, Warning, TEXT("Report: %s"), *report);
}
