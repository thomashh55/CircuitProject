// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "VoltageSource.h"


const FString AVoltageSource::m_prefix = FString("V");

// Sets default values
AVoltageSource::AVoltageSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_directCurrent = 0;
}

// Getters and Setters
double AVoltageSource::GetDirectCurrent()
{
	return m_directCurrent;
}

void AVoltageSource::SetDirectCurrent(double directCurrent)
{
	m_directCurrent = directCurrent;
}

// Called when the game starts or when spawned
void AVoltageSource::BeginPlay()
{
	Super::BeginPlay();

	// Create nodes
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
	m_circNodeArray.Add(GetWorld()->SpawnActor<ACircNode>(ACircNode::StaticClass()));
}

// Called every frame
void AVoltageSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns NgSpice prefix
FString AVoltageSource::GetPrefix()
{
	return m_prefix;
}

// Returns line for NgSpice
FString AVoltageSource::GetCircLine()
{
	if (m_circNodeArray.Num() == 2 && m_circNodeArray[0] != NULL && m_circNodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_circNodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_circNodeArray[1]->GetId()) + FString(" ") +
			FString::SanitizeFloat(m_directCurrent);
	}
	return FString();
}

