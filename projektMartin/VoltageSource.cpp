// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "VoltageSource.h"


const FString AVoltageSource::m_prefix = FString("V");

// Sets default values
AVoltageSource::AVoltageSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	
}

// Called every frame
void AVoltageSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AVoltageSource::GetPrefix()
{
	return m_prefix;
}

FString AVoltageSource::GetCircLine()
{
	if ((*m_nodeArray)[0] != NULL && (*m_nodeArray)[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt((*m_nodeArray)[0]->GetId()) + FString(" ") +
			FString::FromInt((*m_nodeArray)[1]->GetId()) + FString(" ") +
			FString::SanitizeFloat(m_directCurrent);
	}
	return FString::FromInt(m_nodeArray->Num());
}

