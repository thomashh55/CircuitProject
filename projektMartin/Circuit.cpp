// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "Circuit.h"


// Sets default values
ACircuit::ACircuit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

int32 ACircuit::GetComponentCounter()
{
	return m_componentCounter;
}

void ACircuit::SetComponentCounter(int32 componentCounter)
{
	m_componentCounter = componentCounter;
}

int32 ACircuit::GetCircNodeCounter()
{
	return m_circNodeCounter;
}

void ACircuit::SetCircNodeCounter(int32 circNodeCounter)
{
	m_circNodeCounter = circNodeCounter;
}

/*TArray<AComponent> ACircuit::GetComponentArray()
{
	return m_componentArray;
}
	
void ACircuit::SetComponentArray(TArray<AComponent> componentArray)
{
	m_componentArray = componentArray;
}

TArray<ACircNode> ACircuit::GetCircNodeArray()
{
	return m_circNodeArray;
}

void ACircuit::SetCircNodeArray(TArray<ACircNode> circNodeArray)
{
	m_circNodeArray = circNodeArray;
}*/

// Called when the game starts or when spawned
void ACircuit::BeginPlay()
{
	Super::BeginPlay();

	m_componentCounter = 0;
	m_circNodeCounter = 0;
}

// Called every frame
void ACircuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Simulation commands
void ACircuit::Start()
{

}

