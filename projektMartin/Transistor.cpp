// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
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
	
}

// Called every frame
void ATransistor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ATransistor::GetPrefix()
{
	return m_prefix;
}

FString ATransistor::GetCircLine()
{
	/*if (m_nodeArray[0] != NULL && m_nodeArray[1] != NULL && m_nodeArray[2] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_nodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_nodeArray[1]->GetId()) + FString(" ") +
			FString::FromInt(m_nodeArray[2]->GetId());
	}*/
	return FString();
}

