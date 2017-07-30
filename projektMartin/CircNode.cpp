// Fill out your copyright notice in the Description page of Project Settings.

#include "NewtonProject.h"
#include "CircNode.h"


// Sets default values
ACircNode::ACircNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Getters and Setters
FString ACircNode::GetId()
{
	return m_id;
}

void ACircNode::SetId(FString id)
{
	m_id = id;
}

double ACircNode::GetVoltage()
{
	return m_voltage;
}

void ACircNode::SetVoltage(double voltage)
{
	m_voltage = voltage;
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

