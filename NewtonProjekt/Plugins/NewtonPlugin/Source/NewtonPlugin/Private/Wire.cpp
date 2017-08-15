// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "Wire.h"


const FString AWire::m_prefix = FString("V");

// Sets default values
AWire::AWire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Assigns nodes to the wire
void AWire::AddCircNodes(ACircNode *circNode1, ACircNode *circNode2)
{
	m_circNodeArray.Empty();
	m_circNodeArray.Add(circNode1);
	m_circNodeArray.Add(circNode2);
}

// Gets nodes of this component
TArray<ACircNode*> AWire::GetCircNodeArray()
{
	return m_circNodeArray;
}

// Getter and setter for component identifier
void AWire::SetId(int32 id)
{
	m_id = GetPrefix() + FString::FromInt(id);
}

FString AWire::GetId()
{
	return m_id;
}

// Returns NgSpice prefix
FString AWire::GetPrefix()
{
	return m_prefix;
}

// Returns line for NgSpice
FString AWire::GetCircLine()
{
	if (m_circNodeArray.Num() == 2 && m_circNodeArray[0] != NULL && m_circNodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_circNodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[1]->GetId()) + FString(" 0");
	}
	return FString();
}

// Getters and setters for measurements
double AWire::GetCurrent(int index)
{
	if (index < m_currentArray.Num()) {
		return m_currentArray[index];
	}
	return 0;
}

void AWire::AddCurrent(double current)
{
	m_currentArray.Add(current);
}

void AWire::ResetCurrentArray()
{
	m_currentArray.Empty();
}