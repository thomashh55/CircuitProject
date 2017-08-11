// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"

#include "Transistor.h"


const FString ATransistor::m_prefix = FString("Q");

// Sets default values
ATransistor::ATransistor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATransistor::BeginPlay()
{
	Super::BeginPlay();

	// Create nodes
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
}

// Called every frame
void ATransistor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns NgSpice prefix
FString ATransistor::GetPrefix()
{
	return m_prefix;
}

// Returns line for NgSpice
FString ATransistor::GetCircLine()
{
	if (m_circNodeArray.Num() == 3 && m_circNodeArray[0] != NULL && m_circNodeArray[1] != NULL && m_circNodeArray[2] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_circNodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[1]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[2]->GetId()) + FString(" QNPN");
	}
	return FString();
}

