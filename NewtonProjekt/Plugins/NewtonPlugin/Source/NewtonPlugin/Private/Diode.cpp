// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "Diode.h"


const FString ADiode::m_prefix = FString("D");

// Sets default values
ADiode::ADiode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADiode::BeginPlay()
{
	Super::BeginPlay();

	// Create nodes
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
}

// Called every frame
void ADiode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns NgSpice prefix
FString ADiode::GetPrefix()
{
	return m_prefix;
}

// Returns line for NgSpice
FString ADiode::GetCircLine()
{
	if (m_circNodeArray.Num() == 2 && m_circNodeArray[0] != NULL && m_circNodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_circNodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[1]->GetId()) + FString(" D");
	}
	return FString();
}

