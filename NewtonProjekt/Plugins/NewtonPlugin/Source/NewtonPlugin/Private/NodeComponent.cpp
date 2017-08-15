// Martin Gulis & Tomas Liscak

#include "CoreMinimal.h"

#include "NodeComponent.h"


// Sets default values
ANodeComponent::ANodeComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANodeComponent::BeginPlay()
{
	Super::BeginPlay();

	// Create nodes
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
}

// Called every frame
void ANodeComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns NgSpice prefix
FString ANodeComponent::GetPrefix()
{
	return "";
}

// Returns line for NgSpice
FString ANodeComponent::GetCircLine()
{
	return "";
}

