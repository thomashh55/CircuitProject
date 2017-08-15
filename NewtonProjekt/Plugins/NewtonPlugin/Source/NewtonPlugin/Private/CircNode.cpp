// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "CircNode.h"


// Sets default values
ACircNode::ACircNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACircNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACircNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Getter and setter for component identifier
int32 ACircNode::GetId()
{
	return m_id;
}

void ACircNode::SetId(int32 id)
{
	m_id = id;
}

// Getters and setters for measurements
double ACircNode::GetVoltage(int index)
{
	if (index < m_voltageArray.Num()) {
		return m_voltageArray[index];
	}
	return 0;
}

void ACircNode::AddVoltage(double voltage)
{
	m_voltageArray.Add(voltage);
}

void ACircNode::ResetVoltageArray()
{
	m_voltageArray.Empty();
}

