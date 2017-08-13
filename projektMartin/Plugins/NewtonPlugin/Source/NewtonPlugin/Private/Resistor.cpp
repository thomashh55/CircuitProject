// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "Resistor.h"


const FString AResistor::m_prefix = FString("R");

// Sets default values
AResistor::AResistor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_resistance = 0;
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

	// Create nodes
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
}

// Called every frame
void AResistor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns NgSpice prefix
FString AResistor::GetPrefix()
{
	return m_prefix;
}

// Returns line for NgSpice
FString AResistor::GetCircLine()
{
	if (m_circNodeArray.Num() == 2 && m_circNodeArray[0] != NULL && m_circNodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_circNodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[1]->GetId()) + FString(" ") +
			FString::SanitizeFloat(m_resistance);
	}
	return FString();
}

