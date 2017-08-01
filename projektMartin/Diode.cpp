// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
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
	
}

// Called every frame
void ADiode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ADiode::GetPrefix()
{
	return m_prefix;
}

FString ADiode::GetCircLine()
{
	/*if (m_nodeArray[0] != NULL && m_nodeArray[1] != NULL) {
		return m_id + FString(" ") +
			FString::FromInt(m_nodeArray[0]->GetId()) + FString(" ") +
			FString::FromInt(m_nodeArray[1]->GetId());
	}*/
	return FString();
}

