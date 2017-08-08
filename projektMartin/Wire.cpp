// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
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

