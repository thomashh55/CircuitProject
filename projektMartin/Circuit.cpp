// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Circuit.h"

//Circuit Log
DEFINE_LOG_CATEGORY(CircuitLog);

// Sets default values
ACircuit::ACircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
/*TArray<AComponent*> ACircuit::GetComponentArray()
{
	return m_componentArray;
}
	
void ACircuit::SetComponentArray(TArray<AComponent*> componentArray)
{
	m_componentArray = componentArray;
}

TArray<ACircNode*> ACircuit::GetCircNodeArray()
{
	return m_circNodeArray;
}

void ACircuit::SetCircNodeArray(TArray<ACircNode*> circNodeArray)
{
	m_circNodeArray = circNodeArray;
}*/

// Called when the game starts or when spawned
void ACircuit::BeginPlay()
{
	Super::BeginPlay();

	// Adds this circuit to NgSpice
	NgSpice::getInstance().AddCircuit(this);
}

// Called before destroing the actor
void ACircuit::BeginDestroy()
{
	Super::BeginDestroy();

	// Removes this circuit from NgSpice
	NgSpice::getInstance().RemoveCircuit(this);
}

// Called every frame
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	int32 m_componentCounter = 0;
	int32 m_circNodeCounter = 0;
	NgSpice &ngspice = NgSpice::getInstance();
	ngspice.Command("circbyline schema");
	for (ACircNode *circNode : m_circNodeArray) {
		circNode->SetId(m_circNodeCounter++);
	}
	for (AComponent *component : m_componentArray) {
		component->SetId(m_componentCounter++);
		UE_LOG(CircuitLog, Warning, TEXT("Circuit: %s"), *component->GetCircLine());
		ngspice.Command(TCHAR_TO_ANSI(*(FString("circbyline ") + component->GetCircLine())));
	}
	ngspice.Command("circbyline .end");
	ngspice.Command("tran 0.1 2 uic");
}

void ACircuit::Report(const FString& report)
{
	UE_LOG(CircuitLog, Warning, TEXT("Report: %s"), *report);
}
